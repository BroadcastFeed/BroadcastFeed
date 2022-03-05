#include "Database.h"
#include <string>

void Database::addUser(std::string newUsername) {
    bool alreadyExists = false;
    for (auto &profile: this->users) {
        if (newUsername == profile.getName()) {
            alreadyExists = true;
        }
    }
    if (!alreadyExists) {
        Profile newUser = Profile(newUsername);
        this->users.push_back(newUser);
    }
}

std::vector<Profile> Database::getUsers() {
    return this->users;
}


Database::operator std::string() const { 
    std::string str;
    str += "Database: \n";
    for(Profile p : this->users) {
        str += (std::string) p + "\n";
    }
    return str; 
}