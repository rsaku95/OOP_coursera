#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <limits>

using namespace std;

string validateInput(string& accountInfo);
double validateBalance(double& balanceValue);

class SecureAccount {
	private:
		string accountNumber;
		string accountOwner;
		string accountType;

		double balance;
		bool isActive;

		vector<string> transactionHistory;

	public:
		SecureAccount(const string& accNum, const string& accOwn, const string& accType, double bal = 0.0) :
					  accountNumber(accNum), accountOwner(accOwn), accountType(accType), balance(bal), isActive(true){
			cout << "Account " << accountNumber <<  " created" << endl;
		}

		~SecureAccount(){
			cout << "Account released" << endl;
		}

		// Getter
		string get_accountNumber() const { return accountNumber; };
		string get_accountOwner() const { return accountOwner; };
		string get_accountType() const { return accountType; };
		double get_balance() const { return balance; };

		// Setter
		


		// Member functions
		void displayAccount() const {
			cout << "Account: " << accountNumber << " | Owner: " << accountOwner
				<< " | Balance: $ " << std::fixed << std::setprecision(2) << balance << endl;
		}
		
		void deposit() {

		}

		friend void transfer(SecureAccount& sec, double balance, string& targetAccount){}

};

void transfer(SecureAccount& sec, double balance, string& targetAccount){}

int main() {
	// acct. number -> length:11 (ex. 00123456789) 00 + 9 numbers
	int choice;
	bool invalid = true;

	try{
		{
			SecureAccount acct("00123456789", "John Doe", "Checking");
			acct.displayAccount();

			cout << "OPERATIONS MENU" << endl;
			cout << "1. View information" << endl;
			cout << "2. Deposit cash" << endl;
			cout << "3. Transfer" << endl;
			cout << "4. Transaction history" << endl;
			cout << "5. Exit" << endl;

			cin.clear();

			do{
				cout << "Choose operation (1-4): ";
				if (!(cin>>choice)){
					cout << "Invalid input!" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else if (choice < 1 || choice > 4) {
					cout << "Choose between 1 and 4!" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else {
					invalid = false;
				}
			} while (invalid);

			switch (choice){
			case 1: // View account information
				acct.displayAccount();
				break;
			case 2: // Deposit cash
				acct.deposit();
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				return 0;
			default:
				break;
			}
		}
	}
	catch (const std::exception& e){
		cout << e.what() << endl;
	}

	return 0;
}

string validateInput(string& accountInfo) {
	if (accountInfo.empty()) {
		throw invalid_argument("Invalid string!");
	}
	else return accountInfo;
}

double validateBalance(double& balanceValue) {
	if (balanceValue < 0.0) {
		throw out_of_range("Number must be positive!");
	}
	else return balanceValue;
}