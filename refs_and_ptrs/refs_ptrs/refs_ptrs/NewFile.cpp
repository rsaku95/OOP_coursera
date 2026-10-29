#include <cmath>
#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>
#include <string>
#include <tuple>

using product_Tuple = std::tuple<std::string, std::string, double>;
using staging_Map = std::map<int, product_Tuple>;

class Product {
private:
    int productId;
    std::string productName;
    std::string productVendor;
    double quantity;
    bool active;

    static bool isValidProductId(int id) {
        return id >= 1000;
    }

    static bool isValidProductName(const std::string& name) {
        return !name.empty();
    }

    static bool isValidVendorName(const std::string& vendor) {
        return !vendor.empty();
    }

    static bool isValidProductQuantity(double value) {
        return std::isfinite(value) && value > 0.0;
    }

public:
    Product(
        int id,
        const std::string& name,
        const std::string& vendor,
        double productQuantity,
        bool productActive)
        : productId(id),
          productName(name),
          productVendor(vendor),
          quantity(productQuantity),
          active(productActive) {
        if (!isValidProductId(id)) {
            throw std::invalid_argument("Product ID must be at least 1000.");
        }

        if (!isValidProductName(name)) {
            throw std::invalid_argument("Product name cannot be empty.");
        }

        if (!isValidVendorName(vendor)) {
            throw std::invalid_argument("Product vendor cannot be empty.");
        }

        if (!isValidProductQuantity(productQuantity)) {
            throw std::invalid_argument(
                "Product quantity must be greater than zero.");
        }

        if (!productActive) {
            throw std::invalid_argument("Product must be active.");
        }
    }

    int getId() const {
        return productId;
    }

    const std::string& getName() const {
        return productName;
    }

    const std::string& getVendor() const {
        return productVendor;
    }

    double getQuantity() const {
        return quantity;
    }

    bool isActive() const {
        return active;
    }

    product_Tuple toRecord() const {
        return { productName, productVendor, quantity };
    }

    void displayInformation() const {
        std::cout << "ID: " << productId
                  << ", Name: " << productName
                  << ", Vendor: " << productVendor
                  << ", Quantity: " << quantity
                  << ", Active: " << std::boolalpha << active
                  << '\n';
    }
};

class DataBaseManager {
private:
    // Database schema:
    // product ID -> product name, vendor, quantity
    staging_Map databaseRecords;

public:
    void writeData(const staging_Map& registry) {
        if (registry.empty()) {
            std::cout << "No records to save.\n";
            return;
        }

        databaseRecords = registry;

        std::cout << "\nDatabase records saved:\n";

        for (const auto& [productId, productData] : databaseRecords) {
            const auto& [name, vendor, quantity] = productData;

            std::cout << "ID: " << productId
                      << ", Name: " << name
                      << ", Vendor: " << vendor
                      << ", Quantity: " << quantity
                      << '\n';
        }
    }

    staging_Map readRegistry() const {
        return databaseRecords;
    }
};

double inputValidation(
    const std::string& prompt,
    double minimumValue = 0.0) {
    while (true) {
        std::cout << prompt;

        std::string input;
        if (!std::getline(std::cin, input)) {
            throw std::runtime_error("Input stream closed.");
        }

        try {
            std::size_t charactersRead = 0;
            const double value = std::stod(input, &charactersRead);

            if (charactersRead != input.size() ||
                !std::isfinite(value) ||
                value < minimumValue) {
                throw std::invalid_argument("Invalid numeric value.");
            }

            return value;
        }
        catch (const std::exception&) {
            std::cout << "Invalid input. Enter a value of at least "
                      << minimumValue << ".\n";
        }
    }
}

std::string nameValidation(const std::string& prompt) {
    while (true) {
        std::cout << prompt;

        std::string value;
        if (!std::getline(std::cin, value)) {
            throw std::runtime_error("Input stream closed.");
        }

        if (!value.empty()) {
            return value;
        }

        std::cout << "Input cannot be empty.\n";
    }
}

int main() {
    try {
        DataBaseManager databaseManager;
        staging_Map registry;

        int orderNumber = 1000;
        bool continueEntering = true;

        while (continueEntering) {
            const std::string productName =
                nameValidation("Enter product name: ");

            const std::string vendorName =
                nameValidation("Enter vendor name: ");

            const double productQuantity =
                inputValidation("Enter quantity: ", 0.000001);

            Product product(
                orderNumber,
                productName,
                vendorName,
                productQuantity,
                true);

            product.displayInformation();

            // Construct the map entry directly in the registry.
            registry.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(product.getId()),
                std::forward_as_tuple(
                    product.getName(),
                    product.getVendor(),
                    product.getQuantity()));

            const int choice = static_cast<int>(
                inputValidation("Exit? (yes:1, no:0): ", 0.0));

            continueEntering = choice != 1;
            ++orderNumber;

            std::cout << '\n';
        }

        std::cout << "BULK SAVE TO DATABASE\n";
        databaseManager.writeData(registry);

        // The staging cache is no longer needed after saving.
        registry.clear();

        std::cout << "\nREAD FROM DATABASE AFTER INPUT\n";

        const staging_Map databaseRecords =
            databaseManager.readRegistry();

        for (const auto& [id, details] : databaseRecords) {
            const auto& [name, vendor, quantity] = details;

            std::cout << "ID: " << id
                      << ", Name: " << name
                      << ", Vendor: " << vendor
                      << ", Quantity: " << quantity
                      << '\n';
        }
    }
    catch (const std::exception& exception) {
        std::cerr << "Error: " << exception.what() << '\n';
        return 1;
    }

    return 0;
}