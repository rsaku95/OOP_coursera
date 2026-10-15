#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

class UserProfile {
private:
	string userName;
	string email;
	string passwordHash;
	string fullName;
	string phoneNumber;

	int age;

	vector<string> friends;

	bool isPrivateProfile;
	bool isVerified;

	bool isValidEmail(const std::string& email) const {
		std::regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
		return std::regex_match(email, emailPattern);
	}

	bool isValidUsername(const std::string& username) const {
		return username.length() >= 3 && username.length() <= 20;
	}
public:
	// Constructor with comprehensive validation
	UserProfile(const std::string& user, const std::string& mail, const std::string& name)
		: isPrivateProfile(true), isVerified(false), age(0) {
		if (!setUsername(user)) {
			throw std::invalid_argument("Invalid username");
		}
		if (!setEmail(mail)) {
			throw std::invalid_argument("Invalid email address");
		}
		if (!setFullName(name)) {
			throw std::invalid_argument("Invalid full name");
		}
	}

	// Getters for public information
	std::string getUsername() const { return userName; }
	std::string getEmail() const { return email; }
	std::string getDisplayName() const {
		return isPrivateProfile ? userName : fullName;
	}

	bool isProfilePrivate() const { return isPrivateProfile; }
	bool isUserVerified() const { return isVerified; }
	int getFriendCount() const { return friends.size(); }

	// Secured setters with validation
	bool setUsername(const std::string& newUsername) {
		if (isValidUsername(newUsername)) {
			userName = newUsername;
			return true;
		}
		std::cout << "Error: Username must be 3-20 characters long" << std::endl;
		return false;
	}
	bool setEmail(const std::string& newEmail) {
		if (isValidEmail(newEmail)) {
			email = newEmail;
			return true;
		}
		std::cout << "Error: Invalid email format" << std::endl;
		return false;
	}
	bool setFullName(const std::string& name) {
		if (!name.empty() && name.length() <= 100) {
			fullName = name;
			return true;
		}
		std::cout << "Error: Full name cannot be empty or exceed 100 characters" << std::endl;
		return false;
	}
	bool setAge(int newAge) {
		if (newAge >= 13 && newAge <= 120) {
			age = newAge;
			return true;
		}
		std::cout << "Error: Age must be between 13 and 120" << std::endl;
		return false;
	}

	// Your implementation here: Add methods for privacy settings, friend management, etc.    
	void setPrivacySettings() {

	}
	// addFriend, removeFriend, with validation
	// 
	
	void set_addFriends() {
		// validate information
	}

	void set_removeFriends() {
		// validate information
	}

	// Friend declarations for platform administration
	friend class PlatformModerator;
	friend void technicalSupport(UserProfile& user, const std::string& issue);
};

class PlatformModerator {

};

static void addFriends(UserProfile &user) {
	// Prompt user name, email , full name 
	
	user.set_addFriends();
}

static void removeFriends(UserProfile& user) {

	user.set_removeFriends();
}

static void technicalSupport(UserProfile& user, const std::string& issue) {}



int main() {
	// Your code here: Create UserProfile objects and demonstrate encapsulation
	UserProfile user("Fulamengano", "fulamengano@gmail.com", "Fulano Mengano");

	return 0;
}

