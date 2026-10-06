#include <iostream>
#include <string>
#include <chrono>
#include <format>

using namespace std;

class DigitalAsset{
    private:
        string filename;
        string filetype;
        double filesize_MB;
        string creationDate;
        bool isActive;
        static int totalAssets; // Track total number of assets created

    public:
        // Default constructor
        DigitalAsset() : filename("untitled"), filetype("unknown"), filesize_MB(0.0), isActive(true){
            // Get current date for creation timestamp
            auto now = chrono::system_clock::now();
            creationDate = format("{:%Y-%m-%d %H:%M:%S}", now);
            totalAssets++;
            cout << "✓ Default asset created: " << filename << " | Total assets: " << totalAssets << endl;
        }
        // Parameterized constructor
        DigitalAsset(const string& fileName, const string& fileType, double fileSize_MB) : filename(fileName), filetype(fileType), filesize_MB(fileSize_MB), isActive(true){
            // Get current date for creation timestamp
            auto now = chrono::system_clock::now();
            creationDate = format("{:%Y-%m-%d %H:%M:%S}", now);
            totalAssets++;
            cout << "✓ Default asset created: " << filename << " | Total assets: " << totalAssets << endl;               
        }
        // Copy constructor
        DigitalAsset(const DigitalAsset& other) : filename(other.filename + "_copy"), filetype(other.filetype), filesize_MB(other.filesize_MB), creationDate(other.creationDate),isActive(other.isActive){
            cout << "✓ Asset copied: " << filename << " from: " << other.filename << " | Total assets: " << totalAssets << endl; 
        }
        // Destructor
        ~DigitalAsset(){
            totalAssets--;
            cout << "✗ Asset destroyed: " << filename << " | Remaining assets: " << totalAssets << endl;
        }

        // Member functions
        void displayInfo() const{
            cout << "Asset: " << filename << " [" << filetype << "] - " << filesize_MB << "MB - Created: " <<creationDate << " - Status: " << (isActive ? "Active" : "Archived") << endl;
        }
        void archive(){
            isActive = false;
            cout << "Asset " << filename << " has been archived." << endl;
        }
        static int getTotalAssets(){
            return totalAssets;
        }
};

int DigitalAsset::totalAssets = 0;
int main(){
    cout << "=== Digital Asset Management System ===" << endl;
    cout << "Initial total assets: " << DigitalAsset::getTotalAssets() << endl;
    cout << endl;
    // Test default constructor
    DigitalAsset digital;
    digital.displayInfo();
    cout << endl;
    // Test parameterized constructor
    
    DigitalAsset logo("logo.png","image",2.5);
    DigitalAsset video("vid.mp4", "video", 255.8);
    
    logo.displayInfo();
    video.displayInfo();
    // Test copy constructor and demonstrate lifecycle
    {
        
    }
    cout << endl;
    return 0;
}