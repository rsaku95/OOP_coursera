#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;

class Character;
int inputValidation(int max_val);

class Character {
	
private:
	string name;
	int hitPoints = 0;
	int attackStrength = 0;

	static const int MAX_HP = 200;
	static const int MAX_AP = 50;

public:
	int damage;

	Character(const string& char_name){
		setName(char_name);
		cout << "Character: " << name << " successfully created." << endl;
	}

	~Character() {
		cout << "Character: " << name << " successfully deleted." << endl;
	}

	// Member functions


	string getName() const { return name; };
	int getHP() const { return hitPoints; };
	int getAP() const { return attackStrength; };

	/*void getHP() const {
		cout << "Hit points: " << hitPoints << endl;
	}
	void getAP() const{
		cout << "Attack strength: " << attackStrength << endl;
	}
	*/
	

	void setName(const string& charName) {
		name = charName;
	}
	// void setHP(int hp)

	void setHP() {
		hitPoints = inputValidation(MAX_HP);
		cout << "Hit points set." << endl;
	}

	void setAP() {
		attackStrength = inputValidation(MAX_AP);
		cout << "Attack strength set." << endl;
	}

	void gameMechanics(){
		damage = inputValidation(MAX_AP);
		damage = std::min(attackStrength, damage);
		hitPoints = std::max(0, hitPoints - damage);
		cout << "Damage dealt: " << endl;
	}

	void displayInfo() const{
		cout << "Name: " << name << ", HP: " << hitPoints << ", Attack: " << attackStrength << endl;
	}

	bool isAlive() const{
		if (hitPoints > 0) {
			return true;
		}
		else return false;
	}

	//friend function - input validation
	friend int inputValidation(int max_val);

	// Friend function - modify HP 
	friend void modifyHP(Character& ch);
};


int inputValidation(int max_val) {
	int input;
	//int val;
	bool valid = true;

	cin.clear();

	do{
		cout << "Enter value: ";
		
		if (!(cin>>input)){
			cout << "Enter a valid number!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (input < 0){
			cout << "Input must be positive" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (input > max_val)
		{
			cout << "Input out of bounds (limit= " << max_val << ")" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else{
			valid = false;
		}
	} while (valid);
	return input;
}

void modifyHP(Character& ch) {
	ch.hitPoints *= 2;
}

int main() {
	
	{
		Character hero("Warrior");
		hero.displayInfo();
		hero.setHP();
		hero.setAP();
		hero.displayInfo();
		
		// After damage
		hero.gameMechanics();
		hero.displayInfo();
		// Drink health potion
		modifyHP(hero);
		hero.displayInfo();
	}

	return 0;
}