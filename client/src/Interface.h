#pragma once 
#include <string>

class Interface{
    private:
        bool reachedEOF = false;
    public:
        void startSession(char* username);
        void showMessage(std::string message);
        void commandNotFound();
        bool requestMessage(std::string& message);
        bool isRunning();
        void exiting();
};