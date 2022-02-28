#pragma once
#include <string>

class Interface{
    public:
        void startSession(char* username);
        void showMessage(std::string message);
        std::string requestMessage();

};