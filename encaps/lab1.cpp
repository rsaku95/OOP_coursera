#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <limits>

using namespace std;

string validateAcctInput(string& accountInfo);
double validateInput(double& value);
bool securityCheck(const string& prompt,int pass_Word);

class SecureAccount {
	private:
		string accountNumber;
		string accountOwner;
		string accountType;

		double balance;
		bool isActive;
		int accountPin;

		static constexpr double MAX_DEPOSIT = 50000; // constexpr for integral types like float, double (not int)
		static constexpr double MAX_WITHDRAWAL = 10000;

		vector<string> transactionHistory;
		
		void logTransactions(const string& transaction) {
			transactionHistory.push_back(transaction);

			if (transactionHistory.size() > 100){
				transactionHistory.erase(transactionHistory.begin());
			}
		}

	public:
		SecureAccount(const string& accNum, const string& accOwn, const string& accType, int pass, double bal = 0.0) :
					  accountNumber(accNum), accountOwner(accOwn), accountType(accType), accountPin(pass), balance(bal), isActive(true) {
			cout << "Account " << accountNumber <<  " created" << endl;
			logTransactions("Account " + accountNumber + " created. Type: " + accountType + ". Initial balance: $" + to_string(balance) + ". Status: " + (isActive? "Active" : "Inactive"));

		}

		~SecureAccount(){
			cout << "Account released" << endl;
			isActive = false;
			logTransactions("Account " + accountNumber + " released. Status: " + (isActive ? "Active" : "Inactive"));
		}

		// Getter
		string get_accountNumber() const { return accountNumber; };
		string get_accountOwner() const { return accountOwner; };
		string get_accountType() const { return accountType; };
		double get_balance() const { return balance; };
		bool get_status() const { return isActive; };

		// Setter
		


		// Member functions

		void checkStatus() const {
			if (!isActive) throw invalid_argument("Error: Cannot deposit to inactive account");
		}

		void displayAccount() const {
			cout << "\n=== Account Information ===" << endl;
			cout << "Account: " << accountNumber << 
					"\nOwner: " << accountOwner << 
					"\nType: " << accountType <<
					"\nBalance: $ " << std::fixed << std::setprecision(2) << balance <<
					"\nStatus: " << (isActive? "Active":"Inactive") << 
					"\nRecent transactions: " << transactionHistory.size() << endl;
		}
		
		void deposit() {
			checkStatus();

			double depositVal;

			cin.clear();
			cout << "Enter deposit amount: ";

			cin >> depositVal;
			depositVal = validateInput(depositVal);
			
			if (depositVal > MAX_DEPOSIT){
				cout << "Deposit cancelled. Exceeded daily limit of: $" << MAX_DEPOSIT << endl;
				logTransactions("Invalid transaction. Exceeded daily deposit limit");
			}
			else {
				balance = balance + depositVal;
				cout << "Deposited: " << depositVal << " successful" << endl;
				logTransactions("Deposited: $" + to_string(depositVal) + ". New balance: $" + to_string(balance) + ".");
			}
			
			displayAccount();
		}

		void withdrawal() {
			checkStatus();

			double withdrawalVal;
			cin.clear();
			cout << "Enter withdrawal amount: ";

			cin >> withdrawalVal;
			withdrawalVal = validateInput(withdrawalVal);
			
			bool validPass;
			int pin = accountPin;

			validPass = securityCheck("Please enter password: ", pin);

			if (!validPass) throw invalid_argument("Password attempts exceeded!");

			if (withdrawalVal > balance){
				logTransactions("Invalid transaction. Attempted to withdraw amount greater than balance.");
				throw out_of_range("Error: Amount is greater than balance.");
			}
			else if (withdrawalVal > MAX_WITHDRAWAL){
				logTransactions("Invalid transaction. Attempted to withdraw amount exceeding daily withdrawal limit.");
				//cout << "Withdrawal cancelled. Exceeded daily limit of: $" << MAX_WITHDRAWAL << endl;
				throw out_of_range("Error: Amount is greater than daily withdrawal limit.");
			}
			else {
				balance = balance - withdrawalVal;
				logTransactions("Withdrew: $" + to_string(withdrawalVal) + ". New balance: $" + to_string(balance) + ".");
			}
		}

		friend void transfer(SecureAccount& sec, string& targetAccount, const double& amount);
		friend void readTx(SecureAccount& sec);
		bool securityCheck(const string& prompt, int pass_Word);

};

void transfer(SecureAccount& sec, string& targetAccount, const double& amount) {
	sec.checkStatus();

	if (sec.balance < amount) {
		throw out_of_range("Amount " + to_string(amount) + " is greater than value");
	}
	else sec.balance = sec.balance - amount;
	cout << "\nSender: " << sec.accountNumber << "\nReceiver: " << targetAccount << "\nAmount: " << amount << "\nRemaining balance: " << sec.balance << endl;
	sec.logTransactions("Transfer recorded. Destination: " + targetAccount + " . Value: $" + to_string(amount));
	cout << endl;
}

void readTx(SecureAccount& sec) {
	sec.checkStatus();

	int len = sec.transactionHistory.size();
	if (sec.transactionHistory.empty()){
		throw logic_error("No transaction history!");
	}
	else{
		for (int i = 0; i < len; i++) {
			cout << to_string(i+1) << "." << sec.transactionHistory[i] << endl;
		}
	}
}

// For transfers and withdrawals at first
bool securityCheck(const string& prompt, int pass_Word) {
	int count = 0;
	bool valid = true;
	signed int passWord;

	do {
		cout << prompt;
		if (!(cin >> passWord)) {
			cout << "Wrong password! Only numbers are accepted. Try again" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (passWord != pass_Word) {
			cout << "Wrong password! Try again" << endl;
			count++;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			continue;
		}

	} while (count < 3);

	return valid;
}

int main() {
	// acct. number -> length:11 (ex. 00123456789) 00 + 9 numbers
	int choice;
	bool invalid = true;
	string receiver = "00987654321";
	string acctNumber = "00123456789";

	validateAcctInput(acctNumber);
	bool keepGoing = true;
	SecureAccount acct(acctNumber, "John Doe", "Checking", 123456);

	while (keepGoing){
		try {
			{
				cout << "\nOPERATIONS MENU" << endl;
				cout << "1. View information" << endl;
				cout << "2. Deposit cash" << endl;
				cout << "3. Withdraw cash" << endl;
				cout << "4. Transfer" << endl;
				cout << "5. Transaction history" << endl;
				cout << "6. Exit" << endl;

				cin.clear();

				do {
					cout << "Choose operation (1-6): ";
					if (!(cin >> choice)) {
						cout << "Invalid input!" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					else if (choice < 1 || choice > 6) {
						cout << "Choose between 1 and 6!" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					else {
						invalid = false;
					}
				} while (invalid);

				switch (choice) {
					case 1: // View account information
						cout << "\nView account information" << endl;
						acct.displayAccount();
						break;
					case 2: // Deposit cash
						cout << "\nDeposit cash" << endl;
						acct.deposit();
						break;
					case 3: // Withdraw cash
						cout << "\nWithdraw cash" << endl;
						acct.withdrawal();
						break;
					case 4: // Transfer
						cout << "\nTransfer" << endl;
						transfer(acct, receiver, 200.00);
						break;
					case 5: // Transaction history
						cout << "\nTransaction history" << endl;
						readTx(acct);
						break;
					case 6: // Exit
						cout << "\nExiting...." << endl;
						keepGoing = false;
						break;
					default:
						throw invalid_argument("Wrong choice");
					}
			}
		}
		catch (const std::exception& e) {
			cout << e.what() << endl;
		}
	}

	return 0;
}

string validateAcctInput(string& accountInfo) {
	if (accountInfo.empty()){
		throw invalid_argument("Invalid account number!");
	}
	else if (accountInfo[0] != '0' && accountInfo[1] != '0' || accountInfo.length() != 11){
		throw invalid_argument("Invalid account number!");
	}
	else return accountInfo;
}

double validateInput(double& value){
	if (!value){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw invalid_argument("Invalid input!");
	}
	else if (value < 0.0){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw out_of_range("Error: Deposit amount must be positive");
	}
	else return value;
}