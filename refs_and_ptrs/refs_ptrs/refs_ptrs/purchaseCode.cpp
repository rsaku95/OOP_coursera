#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <tuple>
#include <limits>
#include <cmath>

using namespace std;
// 1. Structural Aliases for easier readability
using product_Tuple = tuple<string, string, double>;
using staging_Map = map<int, product_Tuple>;

// Core object
class Product {
private:
	int productId;
	string productName;
	string productVendor;
	double quantity;
	bool active;

	map<int, tuple<string, string, double>> products;

	bool isValidProductId(const int& product_id) const {
		if (product_id >= 1000) {
			return true;
		}
		else return false;
	}

	bool isValidProductName(const string& product_name) const {
		if (!product_name.empty()) {
			return true;
		}
		else return false;
	}

	bool isValidVendorName(const string& vendor_name) const{
		if (!vendor_name.empty()) {
			return true;
		}
		else return false;
	}

	bool isValidProductQty(const double& product_qty) const {
		if (product_qty > 0) {
			return true;
		}
		else return false;
	}

	bool isActive(const bool& product_active) const {
		if (product_active) {
			return true;
		}
		else return false;
	}


public:
	Product(const int& prodId, const string& prodName, const string& prodVend, const double& prodQty, bool& active_) :
			productId(prodId), productName(prodName), productVendor(prodVend), quantity(prodQty), active(active_){
		
		if (!setProductId(prodId)) {
			throw invalid_argument("Invalid id");
		}
		if (!setProductName(prodName)){
			throw invalid_argument("Product name cannot be empty.");
		}
		if (!setVendorName(prodVend)){
			throw invalid_argument("Product vendor cannot be empty.");
		}
		if (!setProductQuantity(prodQty)){
			throw invalid_argument("Product quantity must be greater than zero.");
		}
		if (!setActive(active_)){
			throw invalid_argument("Product must be active.");
		}
		cout << "\nProduct intialized" << endl;
	}
	~Product() {
	}

	// Getters

	int getId() const { return productId; }
	const string& getProdName() const { return productName; }
	const string& getProdVendor() const { return productVendor; }
	double getProdQty() const { return quantity; }
	bool getStatus() const { return active; }


	// Secured setters with validation
	
	bool setProductId(const int& prodId){
		if (isValidProductId(prodId)){
			productId = prodId;
			//cout << "productId set!" << endl;
			return true;
		} else return false;
	}

	bool setProductName(const string& prodName){
		if (isValidProductName(prodName)) {
			productName = prodName;
			//cout << "productName set!" << endl;
			return true;
		}
		else return false;
	}

	bool setVendorName(const string& vendName) {
		if (isValidVendorName(vendName)){
			productVendor = vendName;
			//cout << "productVendor set!" << endl;
			return true;
		} else return false;
	}

	bool setProductQuantity(const double& prodQty) {
		if (isValidProductQty(prodQty)) {
			quantity = prodQty;
			return true;
		} else return false;
	}

	bool setActive(bool& active_){
		if (isActive(active_)){
			active = active_;
			//cout << "setActive set!" << endl;
			return true;
		} else return false;
	}
	
	void displayInformation(){
		cout << "Displaying info\n" << endl;

		if (products.empty()) throw out_of_range("Empty");

		for (auto it = products.begin(); it != products.end(); it++) {
			cout << "ID: " << it->first << " Name: " << get<0>(it->second) << " Vendor: " << get<1>(it->second) << " Quantity: " << get<2>(it->second) << endl;
		}
		cout << endl;
	}
};

// saving
class DataBaseManager {
	private:
		staging_Map databaseRecords;

	public:
		void writeData(const staging_Map& stag_reg){
			if (stag_reg.empty()){
				return;
			}
			databaseRecords = stag_reg;

			try
			{
				cout << "\nDatabase.." << endl;
				for (const auto& [prod_ID, prod_info] : stag_reg) {
					//int order_id_ = product_list.
					string temp_name = get<0>(prod_info);
					string temp_vname = get<1>(prod_info);
					double temp_qty = get<2>(prod_info);

					cout << " " << prod_ID << " " << temp_name << " " << temp_vname << " " << temp_qty << endl;
				}
			}
			catch (const std::exception& e) {
				cout << e.what() << endl;
			}
		}

		staging_Map readRegistry() {
			staging_Map regs;

			return regs;
		}

};

double inputValidation(const string& prompt) {

	bool invalid;
	string val;
	double value;

	do{
		invalid = true;
		cout << prompt;

		if (!getline(cin,val)){
			cout << "Invalid input!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			value = stod(val);
			if (value < 0){
				cout << "Invalid input! Input must be positive" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}else invalid = false;
		}
	} while (invalid);
	
	return value;
}

string nameValidation(const string& prompt) {
	
	string name;
	bool invalid;

	cin.clear();
	do {
		invalid = true;

		cout << prompt;

		if (!getline(cin,name))	{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input!" << endl;
		}
		else { 
			invalid = false;
		}

	} while (invalid);

	return name;
}

int main() {
	try{
		int order_number = 1000;
		int choice;

		string product_name, vendor_name;
		double product_qty;
		bool status = true;

		DataBaseManager dbm;
		staging_Map registry;



		while (status) {

			product_name = nameValidation("Enter product name: ");

			vendor_name = nameValidation("Enter vendor name: ");

			product_qty = inputValidation("Enter quantity: ");

			Product prod(order_number, product_name, vendor_name, product_qty, true);
			prod.displayInformation();

			// Construct directly inside vector memory using input elements. 
			registry.emplace(piecewise_construct, forward_as_tuple(order_number), forward_as_tuple(move(product_name), move(vendor_name), product_qty));

			choice = static_cast<int>(inputValidation("Exit? (yes:1, no:0): "));

			if (choice == 1) {
				status = false;
			}

			++order_number;
			cin.clear();
			cout << endl;

		}

		// PHASE 2: BULK SAVE TO DATABASE
		cout << "\nBULK SAVE TO DATABASE" << endl;

		dbm.writeData(registry);

		// Clear staging memory cache now that data is safe in the storage tables
		registry.clear();


		// PHASE 3: READ FROM DATABASE AFTER INPUT
		cout << "\nREAD FROM DATABASE AFTER INPUT" << endl;
		const staging_Map dataBaseRecs = dbm.readRegistry();

		for (const auto& [id, details] : dataBaseRecs) {
			cout << "ID: " << id << "Name: " << get<0>(details) << "Vendor: " << get<1>(details) << "Quantity: " << get<2>(details) << endl;
		}
	}
	catch (const std::exception& e){
		cout << e.what() << endl;
	}


	return 0;
}

// Create Product_db
/*
void product_dbCreation(){	// Check if empty

	auto t = make_tuple(productName, productVendor, quantity);

	if (products.empty()) {
		products.insert({ productId,t });
	}

	else {
		auto it = products.find(productId);
		if (it != products.end()) {
			// If exists - update the value
			get<2>(it->second) += quantity;
		}
		else products.insert({ productId, t }); // If DNE - insert the value
	}
}
*/
