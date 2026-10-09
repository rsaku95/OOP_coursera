#include <iostream>
#include <string>
#include <memory>

using namespace std;

class DatabaseConnection {
private:
	string connectionString;
	string databaseName;
	bool isConnected;
	int connectionID;
	static int nextID;

	// Simulate connection establishment
	bool establishConnection() {
		cout << "Establishing connection to: " << databaseName << "..." << endl;
		// Simulate connection logic
		isConnected = true;
		return true;
	}
	// Simulate connection cleanup
	void closeConnection() {
		if (isConnected){
			cout << "Closing database connection [ID: " << connectionID << "]" << endl;
			isConnected = false;
		}
		cout << endl;
	}
public:
	// Default Constructor
	DatabaseConnection() : connectionString("localhost:5432"), databaseName("default_db"), isConnected(false), connectionID(++nextID) {
		cout << "Creating default database connection [ID: " << connectionID << "]" << endl;
		establishConnection();
	}
	
	// Parameterized Constructor
	DatabaseConnection(const string& connection_string, const string& connection_db) : connectionString(connection_string), databaseName(connection_db),
						isConnected(false), connectionID(nextID++) {
		cout << "Creating default database connection [ID: " << connectionID << "]" << endl;
		establishConnection();
	}

	// Copy Constructor
	DatabaseConnection(const DatabaseConnection& other) :connectionString(other.connectionString), databaseName(other.databaseName + "_copy"),
						isConnected(false), connectionID(nextID++) {
		cout << "Creating copied database connection [ID: " << connectionID << "] based on connection: "
			 << other.connectionID << endl;
		establishConnection();
	}

	// Destructor
	~DatabaseConnection(){
		cout << "Destroying database connection[ID: " << connectionID << "]" << endl;
		closeConnection();
	}

	// Member functions
	void executeQuery(const string& query) {
		if (isConnected){
			cout << "Executing on " << databaseName << ": " << query << endl;
		}
		else{
			cout << "Cannot execute - connection not established" << endl;
		}
	}

	bool getConnectionStatus() const {
		return isConnected;
	}

	int getID() const {
		return connectionID;
	}
};

// Initialize static member
int DatabaseConnection::nextID = 0;

int main() {
	cout << "=== Database Connection Manager ===" << endl;
	// Your code here: Create different types of database connections

	DatabaseConnection db1;
	db1.executeQuery("SELECT * FROM users");
	cout << endl;
	DatabaseConnection db2("localhost:1234", "production_db");
	db2.executeQuery("SELECT COUNT(*) FROM orders");
	cout << endl;
	DatabaseConnection db3("localhost:2345", "test_db");
	db3.executeQuery("SELECT * FROM test_table");
	cout << endl;

	{
		DatabaseConnection db3 = db2;
		db3.executeQuery("SELECT * FROM copied_data");
		cout << "Original connection ID: " << db2.getID() << endl;
		cout << "Copied connection ID: " << db3.getID() << endl;
		cout << endl;
	}
	db2.executeQuery("SELECT * FROM final_query");
	cout << endl;

	return 0;
}
