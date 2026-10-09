#include <iostream>
#include <string>
#include <chrono>
#include <format>
#include <stdexcept>
#include <vector>
#include <array>

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
            // Validate negative file size - reject if negative
            /* If a constructor throws an exception, the object's creation is completely aborted, it is never instantiated in memory, and no resources are leaked.*/
            if (fileSize_MB < 0.0){    // Check if negative
                throw std::invalid_argument("Negative value not allowed");
            }

            // Adding more functionality like file extension validation
            
            size_t pos = fileName.find('.');

            string extension = fileName.substr(pos + 1);
            //int len = sizeof(fileName) / sizeof(fileName[0]);
            //cout << extension << endl;

            while (pos != string::npos) {
                //cout << pos << endl;
                if (extension == "png" || extension == "jpg" || extension == "jpeg") {
                    pos = string::npos; // Set postion to last memory location to break loop
                }
                else throw std::invalid_argument("Invalid extension");  // throw error
            }


            // Get current date for creation timestamp
            auto now = chrono::system_clock::now();
            creationDate = format("{:%Y-%m-%d %H:%M:%S}", now);
            totalAssets++;
            cout << "✓ Default asset created: " << filename << " | Total assets: " << totalAssets << endl;               
        }
        
        // Copy constructor
        DigitalAsset(const DigitalAsset& other) : filename(other.filename + "_copy"), filetype(other.filetype), filesize_MB(other.filesize_MB), creationDate(other.creationDate),isActive(other.isActive){
            totalAssets++;
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
    
    /*
    // Test default constructor
    std::cout << "1. Creating default asset:" << std::endl;
    
    DigitalAsset digital;
    digital.displayInfo();
    cout << endl;
    
    // Test parameterized constructor
    std::cout << "2. Creating specific assets:" << std::endl;
    
    DigitalAsset logo("logo.png", "image", 2.5);
    logo.displayInfo();
    cout << endl;

    try{
        
        DigitalAsset video("vid.mp4", "video", -255.8);
        video.displayInfo();
        cout << endl;
    }
    catch (const std::invalid_argument& e)
    {
        cerr << "Error creating object" << e.what() << "\n";
    }

    cout << endl;
    // Test copy constructor and demonstrate lifecycle
    std::cout << "3. Testing copy constructor:" << std::endl;
    {
        DigitalAsset logo2{ logo };     // Copy constructor called
        logo2.displayInfo();
        logo2.archive();
        std::cout << "--- logoCopy going out of scope ---" << std::endl;
    }       // logoCopy destructor called here
    cout << endl;
    
    std::cout << "4. Final status:" << std::endl;
    std::cout << "Total assets remaining: " << DigitalAsset::getTotalAssets() << std::endl;
    std::cout << "\n=== Program ending - remaining objects will be destroyed ===" << std::endl;
    */

    // Creating arrays of objects to see multiple constructor/destructor calls
    
    vector<DigitalAsset> objectArrays;
    objectArrays.reserve(10);   // Allocate memory for 10 objects -> no constructor called

    array<string, 10> names;
    
    try
    {
        for (int i = 0; i < 10; i++)
        {
            names[i] = "logo_" + to_string(i) + ".png";
            objectArrays.emplace_back(names[i], "image", 255);
            objectArrays[i].displayInfo();
        }
    }
    catch (const std::exception& e)
    {
        cerr << "\nError creating object\n" << e.what() << "\n";
    }


    /*
    for (const auto& item : objectArrays) {
        item.displayInfo();
        //cout << item << endl;
    }*/
    
    //objectArrays[i].displayInfo();
    

    return 0;
}