// refs_ptrs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

int main(){
    string msg = "Hello World!\n";
    string* ptr = &msg;

    cout << "Message: " << msg;

    cout << "Address of message: " << &ptr << endl;
    cout << "Address of Pointer: " << ptr << endl;
    cout << "Value via pointer: " << *ptr << endl;

    string& ref = msg;

    cout << "\nMessage: " << msg << endl;
    cout << "Reference: " << ref << endl;
    cout << "Reference address: " << &ref << endl;

    string** ptr_to_ptr = &ptr;
    cout << "\nPointer to pointer address: " << ptr_to_ptr << endl;
    cout << "Pointer to pointer value: " << **ptr_to_ptr << endl;

    int value = 10;
    int other = 20;

    // 1. Pointer to const: cannot modify the VALUE through this pointer
    const int* ptrToConst = &value;
    cout << "const int*: " << *ptrToConst << endl;
    // *ptrToConst = 50;         ---> ERROR: cannot modify value
    ptrToConst = &other;
    cout << "*ptrToConst: " << *ptrToConst << endl;

    // 2. Const pointer: cannot change WHERE it points
    int* const constrPtr = &value;
    cout << "\nint* const: " << *constrPtr << endl;
    *constrPtr = 50;
    // constPtr = &other;        ---> ERROR: cannot change pointer
    cout << "*constrPtr: " << *constrPtr << endl;

    // 3. Const pointer to const: cannot modify either
    const int* const constPtrToConst = &value;
    cout << "*constPtrToConst: " << *constPtrToConst << endl;
    // *constPtrToConst = 50;    ---> ERROR
    // constPtrToConst = &other; ---> ERROR

    int val = 42;

    // Const reference: cannot modify the value through this reference
    const int& constRef = value;
    cout << "\nconstRef: " << constRef << endl;
    // constRef = 100;           ---> ERROR: cannot modify through const reference

    // Original value can still be modified
    val = 100; 
    cout << "val: " << val << endl;

    int* newPtr = nullptr; // Initialize -> set to nullptr if no valid address yet

    // ALWAYS check for NULL before dereferencing (Dereferencing a nullptr is UNDEFINED behavior)
    if (newPtr != nullptr){
        cout << *newPtr << endl;
    }
    else {
        cout << "Poiner is null" << endl;
    }

    // Set to null after delete
    // delete newPtr;
    // *newPtr = nullptr;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
