#include "ProfileSessionManager.h"

void ProfileSessionManager::addActiveUser(std::string username) {
    this->activeUsers.push_back(username);
}

vector<Profile> ProfileSessionManager::getActiveUsers(){
    return this->activeUsers;
}

bool ProfileSessionManager::userIsActive(std::string username){
    bool found = false;
    for (auto &profile: this->activeUsers) {
        if (username == profile.getName()) {
            found = true;
        }
    }
    return found;
}

void ProfileSessionManager::login(std::string username) {
    this->addActiveUser(username);
}