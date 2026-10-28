#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

using namespace std;

class Product {
private:
	int productId;
	string productName;
	string productVendor;

	map<int, string> products;

	bool isValidProductId(const int& product_id) const {
		if (product_id > 0) {
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

	//

public:
	Product(const int& prodId, const string& prodName, const string& prodVend){
		if (!setProductId(prodId)) {
			throw invalid_argument("Invalid id");
		}
		if (!setProductName(prodName)){
			throw invalid_argument("Invalid name");
		}
		if (!setVendorName(prodVend)){
			throw invalid_argument("Invalid vendor");
		}
	}
	~Product() {}

	int getId() const { return productId; }
	string getProdName() const { return productName; }

	// Secured setters with validation
	
	bool setProductId(const int& prodId){
		if (isValidProductId(prodId)){
			productId = prodId;
			return true;
		} else return false;
	}

	bool setProductName(const string& prodName){
		if (isValidProductName(prodName)) {
			productName = prodName;
			return true;
		}
		else return false;
	}

	bool setVendorName(const string& vendName) {
		if (isValidVendorName(vendName)){
			productVendor = vendName;
			return true;
		} else return false;
	}

};

class Vendor {
private:
	int vendorId;
	string vendorName;

	map<int, string> vendors;

	bool isValidVendorId(const int& vendor_id) const {
		if (vendor_id > 0) {
			return true;
		}
		else return false;
	}

	bool isValidVendorName(const string& vendor_name) const {
		if (!vendor_name.empty()) {
			return true;
		}
		else return false;
	}
	
public:
	Vendor(const int& vendId, const string& vend_Name){
		if (!setVendorId(vendId)) {
			throw invalid_argument("Invalid id");
		}
		if (!setVendorName(vend_Name)) {
			throw invalid_argument("Invalid vendor");
		}
	}
	~Vendor() {}

	int getVendorId() const { return vendorId; }
	string getVendorName() const { return vendorName; }

	// Secured setters with validation
	bool setVendorId(const int& vendId){
		if (isValidVendorId(vendId)) {
			vendorId = vendId;
			return true;
		}
		else return false;
	}

	bool setVendorName(const string& vend_Name){
		if (isValidVendorName(vend_Name)) {
			vendorName = vend_Name;
			return true;
		}
		else return false;
	}
};

class Order {
private:
	int orderId;
public:
	Order(){}
};

int main() {


	return 0;
}

