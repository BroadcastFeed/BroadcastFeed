#include "ProfileSessionManager.h"

void ProfileSessionManager::addActiveUser(std::string username) {
    this->activeUsers.push_back(username);
}

void ProfileSessionManager::login(std::string username) {
    this->addActiveUser(username);
}