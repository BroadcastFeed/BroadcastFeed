#include <iostream>
#include "Interface.h"

void Interface::startSession(char* username){
    std::cout << "Hello " << username << std::endl;
}

void Interface::showMessage(std::string message){
    std::cout << message << std::endl;
}

bool Interface::requestMessage(std::string& message){
    std::cout << "> ";
    return (bool) std::getline(std::cin, message);
}

void Interface::commandNotFound(){
    std::cout << "Command not found" << std::endl;
}

void Interface::exiting(){
    std::cout << "\nExiting...";
}