#include <iostream>
#include <string>

using namespace std;

class Character {
private:
	int health_;
	int level_;

public:
	const string name; // Public const: can read, can't modify

	Character(string n, int health, int level) : name(n), health_(health), level_(level) {}

	// Copy consutrcotr - lets us see when copies happen
	Character(const Character& other) : name(other.name), health_(other.health_), level_(other.level_) {
		cout << name << " was copied!" << endl;
	}
	~Character() { cout << name << " was deleted" << endl; }

	// Return by value (makes a copy)
	int getLevel() const { return level_; }
	
	// Return by const reference (no copy, read-only access)
	const int& getHealth() const { return health_; }
};

// For small, cheap-to-copy types (int, char, etc.)
void displaybyValue(Character c) {
	cout << c.name << " at level " << c.getLevel() << endl;
}

// Default choice for objects you don't need to modify
void displaybyReference(const Character& c){
	cout << c.name << " at level " << c.getLevel() << endl;
}

// When null is a valid input, or for optional parameters
void displaybyPointer(const Character* c) {
	cout << c->name << " at level " << c->getLevel() << endl;
	//cout << (*c).name << " at level " << (*c).getLevel() << endl; // Alternative
}

void function() {
	// Heap allocation - object survives beyond this scope
	Character* hero = new Character{ "Hero", 100, 10 };
	cout << hero->name << endl;
	cout << hero->getLevel() << endl;

	delete hero; // Manually free the memory
	hero = nullptr; // Good practice: prevent dangling pointer

	// Stack ---> Type obj; (Automatic, scope-based, lifetime); very fast; size limit limited (1-8 MB); Stack-overflow risk
	// Heap  ---> Type* ptr = new Type; (manual life time, until delete); slower(allocate memory takes time); large size limit (dependent on available RAM); memory leaks/fragmentation risk
	
	/* 
		Stack allocation preferred in modern C++

		If heap allocation is needed, use smart pointers to avoid memory leaks (insted of raw new/delete).
	*/
}

int main() {
	
	{
		Character knight("Sir Galahad", 100, 5);
		cout << knight.name << endl; // Direct access to const member
		cout << knight.getLevel() << endl; // Returns copy
		cout << knight.getHealth() << endl; // Returns const reference
		Character knight2 = knight;

		cout << "\nPass by value" << endl;
		displaybyValue(knight); // Copy constructor called
		cout << "\nPass by reference" << endl;
		displaybyReference(knight); // No Copy
		cout << "\nPass by pointer" << endl;
		displaybyPointer(&knight); // Pass address, no copy

	}
	function();

	/*
	*	Uninitialized pointers contain random memory address so deferencing it could create undefined behavior as it could read/write anywhere in memory.
	*		
	*	int* safePtr = nullptr;
	*	int value = 10;
	*	int* validPtr = &value;
	* 
	*	Dangling pointers: point to freed memory or variable gone out-of-scope
	*	int* ptr = new int{42};
	*	delete ptr;	--> freed (now dangling -> holds old address)
	*	ptr = nullptr; --> fix
	* 
	*/

	cout << endl;
	int numbers[] = {1,2,3,4,5};
	int* ptr = numbers; // points to 1st element

	for (int i = 0; i < 5; i++){
		cout << "Element " << i << ": " << *ptr << endl;
		ptr++;
	}

	ptr = numbers;
	cout << "\n3rd element: " << *(ptr + 2) << endl;

	/*
	*   pointers store memory addresses, use *ptr to access value (dereferencing)
	*	references -> aliases; user without special operators (&:address, ->:member access) 
	* 
	*	const int* -> pointer to const      --> cant change value
	*	int* const -> const pointer to int  --> cant change address
	*	const int& -> const reference		--> cant modify value through reference
	* 
	*  pass large objects by const reference to avoid copying
	*  initialized pointers to nullptr if no valid address
	*  check for nullptr before dereferencing
	*  set pointers to nullptr after deleting
	*  Prefer references when null or assignment is not needed
	*  prefer stack allocation to heap; use smart pointers with heap
	*/


	return 0;
}