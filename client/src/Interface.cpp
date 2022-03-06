#include <iostream>
#include "Interface.h"

void Interface::startSession(char* username){
    std::cout << "Hello " << username << std::endl;
}

void Interface::showMessage(std::string message){
    std::cout << message << std::endl;
}

std::string Interface::requestMessage(){
    std::cout << "> ";
    std::string message;
    std::getline(std::cin, message);
    return message;
}

void Interface::commandNotFound(){
    std::cout << "Command not found" << std::endl;
}