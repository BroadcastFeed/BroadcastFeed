#include "Database.h"
#include <string>

bool Database::userExists(const std::string username){
    for (auto &profile: this->users) {
        if (username == profile.getName()) {
            return true;
        }
    }
    return false;
}

void Database::addUser(const std::string& newUsername) {
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

Profile Database::getUser(const std::string& username){
    Profile nullProfile = Profile(nullptr);
    for (auto &profile: this->users) {
        if (username == profile.getName()) {
            return profile;
        }
    }
    return nullProfile;
}

Database::operator std::string() const { 
    std::string str;
    str += "Database: \n";
    for(const Profile& p : this->users) {
        str += (std::string) p + "\n";
    }
    return str; 
}