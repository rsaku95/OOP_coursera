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
 * validateAcctInput
 * -----------------
 * Validate a provided account number string.
 *
 * Parameters:
 *   accountInfo - reference to account number string to validate
 *
 * Returns:
 *   The same account number string if valid.
 *
 * Throws:
 *   invalid_argument if the account number is empty, does not start with
 *   two leading zeros, or is not 11 characters long.
 *
 * Notes:
 *   This is a minimal validation used by the sample program; real systems
 *   require stricter checks.
 */


string validateAcctInput(string& accountInfo);

/**
 * validateInput
 * -------------
 * Validate a numeric monetary input (double).
 *
 * Parameters:
 *   value - reference to the numeric value to validate
 *
 * Returns:
 *   The same value if valid.
 *
 * Throws:
 *   invalid_argument if the input could not be read,
 *   out_of_range if the value is negative.
 *
 * Notes:
 *   This function assumes input has already been read into `value`.
 *   It performs common error handling for console input streams.
 */
double validateInput(double& value);


static double inputValidation();
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
		 */

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
		 */
		SecureAccount(const string& accNum, const string& accOwn, const string& accType, const int& pass, double bal = 0.0) :
					  accountNumber(accNum), accountOwner(accOwn), accountType(accType), accountPin(pass), balance(bal), isActive(true) {
			// Validate BEFORE assigning to private data

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
			cout << "Account released" << endl;
			isActive = false;
			logTransactions("Account " + accountNumber + " released. Status: " + (isActive ? "Active" : "Inactive"));
		}

		// Getters (simple accessors)
		string get_accountNumber() const { return accountNumber; };
		string get_accountOwner() const { return accountOwner; };
		string get_accountType() const { return accountType; };
		double get_balance() const { return balance; };
		bool get_status() const { return isActive; };
		
		double get_MAX_DEPOSIT() const { return MAX_DEPOSIT; };
		double get_MAX_WITHDRAWAL() const { return MAX_WITHDRAWAL; };



		void set_balance(double newBalance) {
			balance += newBalance;
			logTransactions("Deposited(Withdrew): $" + to_string(newBalance) + ". New balance: $" + to_string(balance) + "."); 
		}

		const string& prompt = "Please enter password: ";
		
		/*bool set_validation(int pin) {
			bool passVal;

			if (pin != accountPin){
				passVal = false;
			}

			if (!passVal) {
				logTransactions("SECURITY ALERT: Invalid transaction. Password attempts exceeded!");
				throw invalid_argument("Password attempts exceeded!");
			}
			else return true;
		}*/

		// Member functions
		
		/**
		 * checkStatus
		 * -----------
		 * Throw if account is inactive. Used to prevent operations on closed
		 * accounts.
		 */

		void checkStatus() const {
			if (!isActive) throw invalid_argument("Error: Cannot deposit to inactive account");
		}

		/**
		 * displayAccount
		 * --------------
		 * Print a concise account summary and the count of recent transactions.
		 */

		/*void displayAccount() const {
			cout << "\n=== Account Information ===" << endl;
			cout << "Account: " << accountNumber << 
					"\nOwner: " << accountOwner << 
					"\nType: " << accountType <<
					"\nBalance: $ " << std::fixed << std::setprecision(2) << balance <<
					"\nStatus: " << (isActive? "Active":"Inactive") << 
					"\nRecent transactions: " << transactionHistory.size() << endl;
		}*/
		
		/**
		 * deposit
		 * -------
		 * Interactive deposit operation:
		 *   - prompts user for an amount,
		 *   - validates input,
		 *   - enforces MAX_DEPOSIT limit,
		 *   - updates balance and logs the transaction.
		 *
		 * Throws:
		 *   invalid_argument / out_of_range via validateInput or on limit violation.
		 */

		/*void deposit() {
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
		}*/

		/**
		 * withdrawal
		 * ----------
		 * Interactive withdrawal operation:
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

		/*void withdrawal() {
			checkStatus();

			double withdrawalVal;
			cin.clear();
			cout << "Enter withdrawal amount: ";

			cin >> withdrawalVal;
			withdrawalVal = validateInput(withdrawalVal);
			
			bool validPass;
			int pin = accountPin;

			validPass = securityCheck("Please enter password: ", pin);

			if (!validPass){
				logTransactions("SECURITY ALERT: Invalid transaction. Password attempts exceeded!");
				throw invalid_argument("Password attempts exceeded!");
			}
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
		}*/

		bool securityCheck() {

			int count = 0;
			bool valid = false;
			int passWord;
			
			cin.clear();
			do {
				cout << prompt;
				if (!(cin >> passWord)) {
					count++;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Wrong password! Try again" << endl;
					logTransactions("SECURITY ALERT: Invalid transaction. Password attempt:" + to_string(count) + ".");
				}
				else if (passWord != accountPin) {
					count++;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Wrong password! Try again" << endl;
					logTransactions("SECURITY ALERT: Invalid transaction. Password attempt:" + to_string(count) + ".");
				}
				else {
					valid = true;
					//return valid;
				}
			} while (!valid && count < 3);
			return valid;
		}

		// Friend functions to allow external transfer and reading of transactions.
		friend void transfer(SecureAccount& sec, const string& targetAccount);
		friend void readTx(SecureAccount& sec);

		/**
		 * securityCheck
		 * -------------
		 * Simple PIN check that prompts the user for a numeric PIN up to 3 times.
		 *
		 * Parameters:
		 *   prompt    - message to show when asking for the PIN
		 *   pass_Word - expected numeric PIN
		 *
		 * Returns:
		 *   true if the correct PIN was entered within allowed attempts, false otherwise.
		 *
		 * Notes:
		 *   - This is a console-based demonstration; do NOT use in production.
		 */

		//friend void securityCheck(SecureAccount& sec, const string& prompt, int pass_Word);
};

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
 */

void transfer(SecureAccount& sec, const string& targetAccount) {
	sec.checkStatus();

	double cashTransfer;
	cashTransfer = inputValidation();

	bool securityFlag;
	securityFlag = sec.securityCheck();

	if (securityFlag) {
		if (sec.balance < cashTransfer) {
			sec.logTransactions("Invalid transaction. Attempted to transfer amount exceeds balance.");
			throw out_of_range("Amount " + to_string(cashTransfer) + " is greater than value");
		}
		else if (cashTransfer > sec.MAX_WITHDRAWAL) {
			sec.logTransactions("Invalid transaction. Attempted to transfer amount exceeding daily transfer limit.");
			throw out_of_range("Error: Amount is greater than daily transfer limit.");
		}
		else {
			sec.balance = sec.balance - cashTransfer;
			cout << "\nSender: " << sec.accountNumber << "\nReceiver: " << targetAccount << "\nAmount: " << cashTransfer << "\nRemaining balance: " << sec.balance << endl;
			sec.logTransactions("Transfer recorded. Destination: " + targetAccount + " . Value: $" + to_string(cashTransfer));
		}
	}
	else {
		sec.logTransactions("SECURITY ALERT: Invalid transaction. Password attempts exceeded!");
		throw invalid_argument("Operation cancelled!.");
	}
}
/**
 * readTx
 * ------
 * Print the transaction history stored in `sec` in chronological order.
 *
 * Throws:
 *   logic_error if the transaction history is empty.
 */

// SHOULD BE INSIDE CLASS
void readTx(SecureAccount& sec) {
	sec.checkStatus();
	int len = sec.transactionHistory.size();
	if (sec.transactionHistory.empty()){
		throw invalid_argument("No transaction history!");
	}
	else{
		for (int i = 0; i < len; i++) {
			cout << to_string(i+1) << "." << sec.transactionHistory[i] << endl;
		}
	}
}

// For transfers and withdrawals at first
/**
 * SecureAccount::securityCheck (implementation)
 *
 * Interactive console PIN entry:
 *   - accepts only numeric input,
 *   - up to 3 failed attempts,
 *   - returns true on success, false otherwise.
 *///

/*void securityCheck(SecureAccount& sec, int pass_Word) { // Not called from main
	int count = 0;
	bool valid = false;
	int passWord;
	cin.clear();
	
	do {
		cout << prompt;
		if (!(cin >> passWord)) {
			cout << "Wrong password! Try again" << endl;
			count++;
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
			valid = true;
		}

	} while (!valid && count < 3);

	return valid;
}*/

static void depositCash(SecureAccount& sec) {
	sec.checkStatus();
	
	double depositVal; // Declare variable deposit value
	depositVal = inputValidation(); // Call function for data validation - check if data is valid (double)
	
	bool validPass;
	validPass = sec.securityCheck();

	if (validPass){
		if (depositVal > sec.get_MAX_DEPOSIT()) {
			throw out_of_range("Deposit cancelled. Exceeded daily deposit limit.");
		}
		else {
			sec.set_balance(depositVal);
		}
	}
	else throw invalid_argument("Operation cancelled!.");
}

static void withdrawCash(SecureAccount& sec){
	sec.checkStatus();

	double withdrawVal;
	withdrawVal = inputValidation();
	
	bool validPass;
	validPass = sec.securityCheck();

	cin.clear();

	if (validPass){
		if (withdrawVal > sec.get_MAX_WITHDRAWAL()) {
			throw out_of_range("Deposit cancelled. Exceeded daily withdrawal limit.");
		}
		else {
			withdrawVal *= -1;
			sec.set_balance(withdrawVal);
		}
	}
	else throw invalid_argument("Operation cancelled!.");
}

static double inputValidation() {

	bool invalid = false;
	double value;
	cin.clear();

	do {
		cout << "Enter value: ";
		cin >> value;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter a valid input: ";
		}
		else if (value < 0){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter a postive number: ";
		}
		else{
			invalid = true;
		}
	} while (!invalid);
	
	return value;
}


//	Single Responsibility Principle(SRP) : A class or function should have one, and only one, reason to change.
static void displayInformation(const SecureAccount& sec){
	cout << "\n=== Account Information ===" << endl;

	cout << "Account: " << sec.get_accountNumber() <<
			"\nOwner: " << sec.get_accountOwner() <<
			"\nType: " << sec.get_accountType() <<
			"\nBalance: $ " << std::fixed << std::setprecision(2) << sec.get_balance() <<
			"\nStatus: " << (sec.get_status() ? "Active" : "Inactive") << endl;
			//"\nRecent transactions: " << transactionHistory.size() << endl;
}


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
 */

int main() {
	// acct. number -> length:11 (ex. 00123456789) 00 + 9 numbers
	int choice;
	bool invalid;
	string receiver = "00987654321";
	string acctNumber = "00123456789";

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
		auto end = chrono::high_resolution_clock::now();
	}

	return 0;
}

/* Implementation of the two simple validators (documented above) */

/**
 * validateAcctInput
 */
string validateAcctInput(string& accountInfo) {
	if (accountInfo.empty()){
		throw invalid_argument("Invalid account number!");
	}
	else if (accountInfo.length() != 11 || accountInfo[0] != '0' && accountInfo[1] != '0') {
		throw invalid_argument("Invalid account number!");
	}
	else return accountInfo;
}

/**
 * validateInput
 */
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