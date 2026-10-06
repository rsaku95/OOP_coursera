#include <iostream>

class Example {
private:
    int data_;

public:
    // Constructor
    Example(int data) : data_(data) {
        std::cout << "Constructor" << ". Data: " << data << std::endl;
    }

    // Destructor
    ~Example() {
        std::cout << "Destructor" << std::endl;
    }

    // Copy constructor
    Example(const Example& other) : data_(other.data_) {
        std::cout << "Copy constructor" << ". Data: " << other.data_ << std::endl;
    }

    // Copy assignment operator
    Example& operator=(const Example& other) {
        std::cout << "Copy assignment" << ". Data: " << other.data_ << std::endl;
        if (this != &other) {
            data_ = other.data_;
        }
        return *this;
    }
};

int main() {
    Example obj1{10};       // Constructor
    Example obj2{20};       // Constructor
    Example obj3{obj1};     // Copy constructor
    obj1 = obj3;            // Copy assignment
    return 0;
}   // Three destructors called