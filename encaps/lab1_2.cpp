#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <limits>

using namespace std;

static bool promptValidation(const string& prompt, const string& otherUser);

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

	void friendsList_mod(const string& instruction, const string& friend_) {
		if (instruction == "add") {
			friends.push_back(friend_);
		}
		else if (instruction == "remove") {
			friends.erase(find(friends.begin(), friends.end(), friend_));
		}
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
		cout << "User profile created..." << endl;
	}
	~UserProfile() {
		cout << "User profile deleted..." << endl;
	}

	// Getters for public information
	std::string getUsername() const { return userName; }
	std::string getEmail() const { return email; }
	std::string getDisplayName() const { return isPrivateProfile ? userName : fullName; }

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
	void setPrivacySettings(bool privacy) {
		if (privacy) {
			isPrivateProfile = true;
		}
		else isPrivateProfile = false;
	}
	// addFriend, removeFriend, with validation
	// 

	void set_addFriends(const string& request){
		// Check if friends is empty
		if (friends.empty()) throw out_of_range("No friends in list.");
		
		//check if already exists
		bool exists = true;

		for (const auto& name :friends){
			if (name == request) {
				break;
			}
			else exists = false;
		}
		
		if (!exists) {
			friendsList_mod("add", request);
			cout << request << " added to friends!" << endl;
		}
		else cout << "Friend already exists!" << endl;
		
	}

	void set_removeFriends(const string& delFriend) {
		// Check if friends is empty
		if (friends.empty()) throw out_of_range("No friends in list.");

		//check if already exists
		bool exists = true;

		for (const auto& name : friends) {
			if (name == delFriend) {
				break;
			}
			else exists = false;
		}

		if (exists) {
			friendsList_mod("remove", delFriend);
			cout << delFriend << " removed from friends!" << endl;
		} else cout << "Friend does not exist!" << endl;
	}

	// Friend declarations for platform administration
	friend class PlatformModerator;
	friend void technicalSupport(UserProfile& user, const std::string& issue);
};

class PlatformModerator {
	public:
		static void performModeration(const UserProfile& user) {
			cout << "\n=== MODERATION REVIEW ===" << std::endl;
			cout << "Full access to: " << user.userName << std::endl;
			cout << "Real name: " << user.fullName << std::endl;
			cout << "Email: " << user.email << std::endl;
			cout << "Age: " << user.age << std::endl;
			cout << "Friend count: " << user.friends.size() << std::endl;
		}
};

/*
**	Input: friend request 
**
**
**  Output: decision (true/false) 
** 
*/

static void acceptFriendRequest(UserProfile& user, const string& otherUser) {
	// Prompt user name, email , full name 
	bool decision;
	// Prompt if User wants to accept friend

	//cout << user.getDisplayName() << "has requested to follow you. Do you wish to accept? (Yes/No): ";
	decision = promptValidation("Has requested to follow you. Do you wish to accept? (Yes/No): ", otherUser);


	if (decision){
		// Accept user
		cout << otherUser << " request accepted" << endl;
		user.set_addFriends(otherUser);
	}
	else {
		cout << otherUser << " request denied" << endl;
	}
}
static void removeFriends(UserProfile& user, const string& removeFriend) {

	bool removeDecision;

	removeDecision = promptValidation("Removing from your friends. Please confirm (Yes / No): ", removeFriend);
	// Check if exists

	if (removeDecision){
		cout << removeFriend << " removed" << endl;
		user.set_removeFriends(removeFriend);
	}
	else{
		cout << removeFriend << " not removed" << endl;
	}	
}

void technicalSupport(UserProfile& user, const std::string& issue) {
	cout << "Technical Support accessing account: " << user.userName << endl;
	cout << "Issue: " << issue << endl;
	cout << "Contact email: " << user.email << endl;
}

static bool promptValidation(const string& prompt, const string& otherUser){

	bool accept;
	string decision;

	cin.clear();
	do{
		accept = false;
		cout << prompt;
		
		if (!(getline(cin, decision))) {
			cout << "Invalid answer!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (decision == "Yes" || decision == "yes") {
			accept = true;
			cin.clear();
		}
		else if (decision == "No" || decision == "no") {
			accept = false;
			cin.clear();
		}
		else {
			cout << "Invalid answer!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (!accept);

	return accept;
}

int main() {
	// Your code here: Create UserProfile objects and demonstrate encapsulation
	
	// list of friends
	vector<string> friend_list = { "Fulano", "Mengano", "Ciclano", "Juninho", "Zeze" };


	try{
		{
			UserProfile user("Fulamengano", "fulamengano@gmail.com", "Fulano Mengano");
			user.setAge(25);
			user.getDisplayName();
			acceptFriendRequest(user, friend_list[0]);
			acceptFriendRequest(user, friend_list[1]);
			acceptFriendRequest(user, friend_list[2]);
			// user.getFriendCount();
			removeFriends(user, friend_list[0]);
			PlatformModerator::performModeration(user);
			technicalSupport(user, "Random error");
		}
	}
	catch (const std::exception& e){
		cout << e.what() << endl;
	}

	return 0;
}

