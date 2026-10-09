#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

// Class tasked with managing file resources.
class ResourceHandler {
private:
	fstream* fileStream; // Points to a shared stream, needed for multiple objects writing to the same file. Avoids: objects overwriting each other's data, or constantly resetting the file pointer.
	string filePath;
	bool isResourceOpen;

public:
	// Default constructor - RAII: Initialize without binding to resource
	ResourceHandler() : fileStream(nullptr), filePath(""), isResourceOpen(false) {	// fileStream pointer initalized, but not pointing to any object.
		cout << "ResourceHandler created (no resource bound)" << endl;
	}

	// Parameterized constructor
	ResourceHandler(const string& file_path) : filePath(file_path), isResourceOpen(false) {
		fileStream = new fstream(); // Creates memory space for a file stream
		fileStream->open(filePath, std::ios::in | std::ios::out | std::ios::app); // Opens file (accesses filStream through pointer to open it)

		if (fileStream->is_open()) {
			isResourceOpen = true;
			cout << "Resource acquired: " << filePath << endl;
		}
		else {
			delete fileStream; // deletes memory space
			fileStream = nullptr; // Sets pointer to point at invalid location.
			throw std::invalid_argument("Failed to acquire resource: " + filePath);
		}
	}

	// Copy constructor
	ResourceHandler(const ResourceHandler& other) : filePath(other.filePath), isResourceOpen(false) {
		fileStream = new fstream(); // Creates memory space for a file stream
		if (other.isResourceOpen) { // Check if resource was created
			fileStream->open(filePath, std::ios::in | std::ios::out | std::ios::app);
			if (fileStream->is_open()) {
				isResourceOpen = true;
				cout << "Resource copied: " << filePath << endl;
			}
			else {
				delete fileStream;
				fileStream = nullptr;
				throw std::invalid_argument("Failed to copy resource: " + filePath);
			}
		}
		else {
			fileStream = nullptr; // Set the pointer to null
			cout << "Copied ResourceHandler (no active resource)" << endl;
		}
	}

	// Destructor
	~ResourceHandler() {
		if (isResourceOpen && fileStream) {
			fileStream->close();
			cout << "Resource released: " << filePath << endl;
		}
		delete fileStream;
		cout << "ResourceHandler destroyed" << endl;

	}

	// Member functions

	bool isOpen() const { // Check if resource is available
		return isResourceOpen;
	}

	void writeData(const string& data) { // Write to resource
		if (isResourceOpen && fileStream) { // Check if resource is available and file is open
			*fileStream << data << endl; // write to file
			cout << "Data written to: " << filePath << endl;
		}
		else {
			cout << "Cannot write - resource not available" << endl;
		}
	}
};

int main() {
	
	cout << "=== Testing ResourceHandler ===" << endl;
	ResourceHandler handler1;
	cout << handler1.isOpen() << endl;
	cout << endl;
	
	{
		ResourceHandler handler2("test_file.txt");
		handler2.isOpen();
		if (handler2.isOpen()){
			handler2.writeData("Testing RAII resource management");
		}
		cout << endl;

		// Test Copy constructor
		ResourceHandler handler3 = handler2;
		handler3.isOpen();
		handler3.writeData("Testing RAII resource management - from copy constructor");
		std::cout << "\n=== Objects going out of scope ===\n" << std::endl;
	}
	
	cout << endl;

	try
	{
		ResourceHandler handler4("invalid / path / file.txt");
		handler4.isOpen();
		handler4.writeData("This should fail");
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	std::cout << "\n=== Program ending ===" << std::endl;

	return 0;
}