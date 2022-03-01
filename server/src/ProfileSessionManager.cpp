#include "ProfileSessionManager.h"

void ProfileSessionManager::addUser(std::string username){
    this->database.addUser(username);
}

void ProfileSessionManager::login(std::string username){
    this->addUser(username);
}