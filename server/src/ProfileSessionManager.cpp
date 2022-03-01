#include "ProfileSessionManager.h"

bool ProfileSessionManager::consultUsername(std::string username){
    return true;
    //not implemented
}

void ProfileSessionManager::addNewUser(std::string username){
    this->database.addUser(username);
}

void ProfileSessionManager::login(std::string username){
    if (!this->consultUsername(username)){
        this->addNewUser(username);
    }
}