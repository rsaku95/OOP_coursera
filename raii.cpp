#include <iostream>
#include <fstream>
#include <string>

class Log{
    private:
        std::ofstream file_;

    public:
        // Constructor: acquire resource (open file)
        explicit Log(const std::string& filename) : file_(filename, std::ios::app) {
            std::cout << "Constructor: file opened" << std::endl;
        }

        // Destructor: release resource (close file)
        ~Log(){
            if (file_.is_open()){
                file_.close();
            }
            std::cout << "Destructor: file closed" << std::endl;
        }

        // Delete copy operations - file handle is unique
        Log(const Log&) = delete;
        Log& operator=(const Log&) = delete;

        // Public interface for writing
        void write(const std::string& message){
            if (file_.is_open()){
                file_ << message << std::endl;
            }
            else{
                std::cerr << "Not file open" << std::endl;
            }
        }
};

int main(){

    {
        Log logger("application.log");
        logger.write("Application started");
        logger.write("Processing data...");
        logger.write("Application finished");
    } // Destructor called automatically - file closed

    std::cout << "Log object has been destroyed" << std::endl;
    return 0;
}