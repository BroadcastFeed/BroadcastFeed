#include <iostream>
#include "Interface.h"

void Interface::startSession(char* username){
    //std::cout << "Session Started for profile " << username << std::endl;
}

void Interface::showMessage(std::string message){
    std::cout << message << std::endl;
}

std::string Interface::requestMessage(){
    std::cout << "> ";
    std::string message;
    std::cin >> message;
    return message;
}