/*
* File:    lab1.cpp
* Project: OOP_coursera - encaps
* Author:  (original author)
* Purpose:
*   A small console program demonstrating an encapsulated bank account type
*   with simple operations: deposit, withdrawal, transfer and transaction
*   history. Includes basic input validation and a simple password check.
*
* Notes:
*   - This file is intentionally simple for teaching OOP / encapsulation.
*   - Limits: MAX_DEPOSIT and MAX_WITHDRAWAL enforce per-operation caps.
*   - Transaction history keeps the most recent 100 entries.
*
* Usage:
*   Build and run with a C++17-compatible toolchain. Program runs as an
*   interactive console application.
*
* See also:
*   - validateAcctInput: basic account number validation
*   - validateInput: numeric input validation for money amounts
*/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <chrono>

using namespace std;

/**
* SecureAccount
* -------------
* Small encapsulation example representing a bank account. This class:
*   - stores account details (number, owner, type),
*   - stores a PIN for a simple security check,
*   - supports deposit, withdrawal, display and maintains a transaction log.
*
* Key behaviors:
*   - Construction logs account creation.
*   - Destruction logs account release and marks the account inactive.
*   - `deposit()` and `withdrawal()` validate input and enforce per-operation
*     limits (MAX_DEPOSIT / MAX_WITHDRAWAL).
*   - `securityCheck` asks for a numeric PIN (up to 3 attempts).
*   - `logTransactions` retains up to the 100 most recent messages.
*
* Exception safety:
*   - Methods throw standard exceptions (invalid_argument, out_of_range,
*     logic_error) on errors, which the sample `main` catches and reports.
*
* Note: This class is intended for demonstration and learning only; it is
* not secure for real financial applications.
**/
class SecureAccount {
	private:
		string accountNumber;
		string accountOwner;
		string accountType;

		double balance;
		bool isActive;
		int accountPin;

		// Per-operation caps (constants)
		static constexpr double MAX_DEPOSIT = 50000; // per-operation cap for deposit
		static constexpr double MAX_WITHDRAWAL = 10000; // per-operation cap for withdraw/transfer

		// Simple in-memory transaction history (recent 100)
		vector<string> transactionHistory;
		
		/**
		 * logTransactions
		 * ----------------
		 * Append a human-readable transaction message to the in-memory log.
		 * If the log exceeds 100 entries, the oldest entry is removed.
		 **/
		void logTransactions(const string& transaction) {
			transactionHistory.push_back(transaction);

			if (transactionHistory.size() > 100){
				transactionHistory.erase(transactionHistory.begin());
			}
		}

	public:

		/**
		 * Constructor
		 *
		 * Parameters:
		 *   accNum  - account number (string)
		 *   accOwn  - account owner name
		 *   accType - account type (e.g., "Checking")
		 *   pass    - numeric PIN for simple security checks
		 *   bal     - optional initial balance (default 0.0)
		 **/
		SecureAccount(const string& accNum, const string& accOwn, const string& accType, const int& pass, double bal = 0.0) :
					  accountNumber(accNum), accountOwner(accOwn), accountType(accType), accountPin(pass), balance(bal), isActive(true) {
			
			/* Validate BEFORE assigning to private data - TBD
			*
			*
			*
			*
			*
			**/

			// Display message
			cout << "Account " << accountNumber <<  " created" << endl;
			// Log transaction
			logTransactions("Account " + accountNumber + " created. Type: " + accountType + ". Initial balance: $" + to_string(balance) + ". Status: " + (isActive? "Active" : "Inactive"));
		}

		/**
		 * Destructor
		 *
		 * Logs account release and marks account inactive.
		 */
		~SecureAccount(){
			// Log transaction
			cout << "Account " << accountNumber << " released." << endl;
			logTransactions("Account " + accountNumber + " released. Status: " + (isActive ? "Active" : "Inactive"));
			isActive = false;
		}

		// Getters (simple accessors)
		string get_accountNumber() const { return accountNumber; };
		string get_accountOwner() const { return accountOwner; };
		string get_accountType() const { return accountType; };
		double get_balance() const { return balance; };
		bool get_status() const { return isActive; };
		
		double get_MAX_DEPOSIT() const { return MAX_DEPOSIT; };
		double get_MAX_WITHDRAWAL() const { return MAX_WITHDRAWAL; };

		// Setters
		// Apply a signed delta to the balance. Positive -> deposit, Negative -> withdrawal
		void applyDelta(double delta) {
			balance += delta;
			if (delta >= 0.0) {
				logTransactions("Deposited: $" + to_string(delta) + ". New balance: $" + to_string(balance) + ".");
			} else {
				logTransactions("Withdrew: $" + to_string(-delta) + ". New balance: $" + to_string(balance) + ".");
			}
		}

		
		// Member functions
		/**
		 * checkStatus
		 * -----------
		 * Throw if account is inactive. Used to prevent operations on closed
		 * accounts.
		 * 
		 **/
		void checkStatus() const {
			cout << "Checking status..." << endl;
			if (!isActive) throw invalid_argument("Error: Cannot deposit to inactive account");
		}

		/**
		 * securityCheck
		 * -------------
		 * Simple PIN check that prompts the user for a numeric PIN up to 3 times.
		 *
		 * Parameters: None
		 *   
		 * Returns:
		 *   true if the correct PIN was entered within allowed attempts, false otherwise.
		 *
		 * Notes:
		 *   - This is a console-based demonstration; do NOT use in production.
		 **/
		bool securityCheck() {

			int count = 0;
			bool valid = false;
			int passWord;
			const string& prompt = "Please enter password: ";

			do {
				cout << prompt;
				cin >> passWord;

				if (cin.fail()) {
					count++;
					
					cout << "Wrong password! Try again" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					
					logTransactions("SECURITY ALERT: Invalid transaction. Password attempt: " + to_string(count) + ".");
				}
				else if (passWord != accountPin) {
					count++;
					
					cout << "Wrong password! Try again" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					
					logTransactions("SECURITY ALERT: Invalid transaction. Password attempt: " + to_string(count) + ".");
				}
				else {
					valid = true;
				}
			} while (!valid && count < 3);
			
			return valid;
		}

		/**
		 * readTx
		 * ------
		 * Print the transaction history stored in 'transactionHistory' in chronological order.
		 *
		 * Throws:
		 *   logic_error if the transaction history is empty.
		 **/
		void readTx() {
			checkStatus();

			int len = transactionHistory.size();
			if (transactionHistory.empty()) {
				throw invalid_argument("No transaction history!");
			}
			else {
				for (int i = 0; i < len; i++) {
					cout << to_string(i + 1) << "." << transactionHistory[i] << endl;
				}
			}
		}

		// Friend functions to allow external transfer and reading of transactions.
		friend void transfer(SecureAccount& sec, const string& targetAccount);
};

string validateAcctInput(const string& accountInfo);
void transfer(SecureAccount& sec, const string& targetAccount);
static void depositCash(SecureAccount& sec);
static void withdrawCash(SecureAccount& sec);
static double inputValidation();
static void displayInformation(const SecureAccount& sec);

/**
* main
* ----
* Small interactive menu demo to exercise the SecureAccount class:
*   1. View information
*   2. Deposit cash
*   3. Withdraw cash
*   4. Transfer
*   5. Transaction history
*   6. Exit
*
* The sample creates a single account and a hard-coded receiver account number
* for transfer demonstration.
**/
int main() {
	
	int choice;
	bool invalid;
	string receiver = "00987654321";
	string acctNumber = "00123456789";	// acct. number -> length:11 (ex. 00123456789) 00 + 9 numbers

	validateAcctInput(acctNumber);
	bool keepGoing = true;
	SecureAccount acct(acctNumber, "John Doe", "Checking", 123456);


	while (keepGoing){
		invalid = true;
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
						//acct.displayAccount();
						displayInformation(acct);
						break;
					case 2: // Deposit cash
						cout << "\nDeposit cash" << endl;
						//acct.deposit();
						depositCash(acct);
						break;
					case 3: // Withdraw cash
						cout << "\nWithdraw cash" << endl;
						//acct.withdrawal();
						withdrawCash(acct);
						break;
					case 4: // Transfer
						cout << "\nTransfer" << endl;
						transfer(acct, receiver);
						break;
					case 5: // Transaction history
						cout << "\nTransaction history" << endl;
						acct.readTx();
						//readTx(acct);
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
		auto end = chrono::high_resolution_clock::now();
	}

	return 0;
}

/* Implementation of the two simple validators (documented above) */
/**
* validateAcctInput
* -----------------
* Validate a provided account number string.
*
* Parameters: accountInfo - reference to account number to validate (string)
*  
* Returns: The same account number string if valid.
*
* Throws:
*   - invalid_argument for empty strings or strings that are incorrectly sized and the first two digits are not zero.
*
* Notes: receiver's acocunt number (string) - This is a minimal validation used by the sample program; real systems require stricter checks.
*  
**/
string validateAcctInput(const string& accountInfo) {
	// Require non-empty, exact length of 11, and leading "00"
	if (accountInfo.empty()){
		throw invalid_argument("Invalid account number!");
	}
	else if (accountInfo.length() != 11 || accountInfo[0] != '0' || accountInfo[1] != '0') {
		throw invalid_argument("Invalid account number!");
	}
	else return accountInfo;
}

/* Implementation of non-member functions */
/**
* transfer
* --------
* Transfer an amount out of `sec` to `targetAccount`.
*   - Performs status check on sender account
*   - Interactive prompt for transfer amount and PIN
*   - Enforces sufficient funds and per-operation transfer limit (MAX_WITHDRAWAL)
*
* Throws:
*   invalid_argument when PIN attempts exhausted,
*   out_of_range for insufficient funds or exceeding limits.
*
* Side effects:
*   Decrements `sec.balance` and logs the transaction message.
**/
void transfer(SecureAccount& sec, const string& targetAccount) {
	sec.checkStatus();

	double cashTransfer;
	cashTransfer = inputValidation();

	bool securityFlag;
	securityFlag = sec.securityCheck();

	if (!securityFlag) {
		// Do not mutate balance on failed authentication
		sec.logTransactions("SECURITY ALERT: Invalid transaction. Password attempts exceeded!");
		throw invalid_argument("Operation cancelled!.");
	}

	// Authorized path
	if (sec.get_balance() < cashTransfer) {
		sec.logTransactions("Invalid transaction. Attempted to transfer amount exceeds balance.");
		throw out_of_range("Amount " + to_string(cashTransfer) + " is greater than value");
	}
	else if (cashTransfer > sec.get_MAX_WITHDRAWAL()) {
		sec.logTransactions("Invalid transaction. Attempted to transfer amount exceeding daily transfer limit.");
		throw out_of_range("Error: Amount is greater than daily transfer limit.");
	}
	else {
		// apply negative delta to reduce balance; print positive transfer amount
		sec.applyDelta(-cashTransfer);
		cout << "\nSender: " << sec.accountNumber << "\nReceiver: " << targetAccount << "\nAmount: " << cashTransfer << "\nRemaining balance: " << sec.get_balance() << endl;
		sec.logTransactions("Transfer recorded. Destination: " + targetAccount + " . Value: $" + to_string(cashTransfer));
	}
}

/**
* depositCash
* -----------
*
* Interactive deposit operation:
*	 - checks account status,
*   - prompts user for an amount,
*   - validates input,
*   - prompts user for password
*   - validates password
*   - enforces MAX_DEPOSIT limit,
*   - updates balance and logs the transaction.
*
* Parameters:
*   - sec: reference to classs
*
* Throws:
*   out_of_range for values that exceed limit or balance
*   invalid_argument for failed security check
**/
static void depositCash(SecureAccount& sec) {
	sec.checkStatus();

	double depositVal; // Declare variable deposit value
	depositVal = inputValidation(); // Call function for data validation - check if data is valid (double)

	bool validPass;
	validPass = sec.securityCheck();

	if (validPass) {
		if (depositVal > sec.get_MAX_DEPOSIT()) {
			throw out_of_range("Deposit cancelled. Exceeded daily deposit limit.");
		}
		else {
			sec.applyDelta(depositVal);
		}
	}
	else throw invalid_argument("Operation cancelled!.");
}

/**
* withdrawCash
* ------------
*
* Interactive withdrawal operation:
*	 - checks account status,
*   - prompts user for an amount,
*   - validates input,
*   - performs a PIN check (up to 3 attempts),
*   - enforces sufficient funds and MAX_WITHDRAWAL,
*   - updates balance and logs the transaction.
*
* Throws:
*   invalid_argument for failed PIN attempts,
*   out_of_range for insufficient funds or exceeding limits.
*/
static void withdrawCash(SecureAccount& sec) {
	sec.checkStatus();

	double withdrawVal;
	withdrawVal = inputValidation();

	bool validPass;
	validPass = sec.securityCheck();

	cin.clear();

	if (validPass) {
		if ((sec.get_balance() <= 0) || sec.get_balance() < withdrawVal) {
			throw out_of_range("Withdrawal cancelled. Not enough funds.");
		}
		else if (withdrawVal > sec.get_MAX_WITHDRAWAL()) {
			throw out_of_range("Withdrawal cancelled. Exceeded daily withdrawal limit.");
		}
		else {
			// apply negative delta to reduce balance
			sec.applyDelta(-withdrawVal);
		}
	}
	else throw invalid_argument("Operation cancelled!.");
}

/**
* inputValidation
* ---------------
*
* Interactive withdrawal operation:
*    - prompts user for an amount,
*    - validates input,
*
* Returns: validated value to be used later (double)
*
**/
static double inputValidation() {

	bool invalid = false;
	double value;
	cin.clear();

	cout << "\nEnter value: ";
	do {
		cin >> value;

		if (cin.fail()) {
			cout << "Enter a valid input: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (value <= 0) {
			cout << "Enter a postive number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else invalid = true;

	} while (!invalid);

	return value;
}

/**
* displayInformation
* --------------
* Print a concise account summary and the count of recent transactions.
*
* Parameters: constant reference to SecureAccount class
*
**/
static void displayInformation(const SecureAccount& sec) {
	cout << "\n=== Account Information ===" << endl;

	cout << "Account: " << sec.get_accountNumber() <<
		"\nOwner: " << sec.get_accountOwner() <<
		"\nType: " << sec.get_accountType() <<
		"\nBalance: $ " << std::fixed << std::setprecision(2) << sec.get_balance() <<
		"\nStatus: " << (sec.get_status() ? "Active" : "Inactive") << endl;
}

//	Single Responsibility Principle(SRP) : A class or function should have one, and only one, reason to change.