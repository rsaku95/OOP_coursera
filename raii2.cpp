#include <iostream>
#include <fstream>
#include <string>

class Log{
    private:
        std::fstream* log_;

    public:
        Log(std::string filename){
            log_ = new std::fstream(filename, std::ios::out | std::ios::app);
            std::cout << "Constructor called." << std::endl;
        }

        Log(const Log& other) = delete;
        Log& operator=(const Log& other) = delete;

        ~Log(){
            if (log_ && log_->is_open()){
                log_->close();
            }
            if(log_ != nullptr){
                delete log_;
                log_ = nullptr;
            }
            std::cout << "Destructor called." << std::endl;
        }
        void write(std::string message){
            if (log_ && log_->is_open()){
                *log_ << message;
            }
        }
};

int main(){
    {
        Log log("log.txt");
        log.write("Hello RAII!\n");
        log.write("RAII -> Resource Acquisition is Initialization\n");
    }
    return 0;
}