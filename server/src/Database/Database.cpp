#include "Database.h"
#include <string>

bool Database::userExists(const std::string& username){
    return users.contains(username);
}

void Database::addUser(const std::string& newUsername) {
    if (!userExists(newUsername)) {
        Profile newUser = Profile(newUsername);
        this->users.insert({newUsername, newUser});
    }
}

// TODO verify const here
std::vector<Profile> Database::getUsers() const {
    vector<Profile> usersVector = {};
    for (std::pair<string, Profile> user : this->users) {
        usersVector.push_back(user.second);
    }

    return usersVector;
}

Profile Database::getUser(const std::string& username){
    return this->users.at(username);
}

Database::operator std::string() const { 
    std::string str;
    str += "Database: \n";
    for(const Profile& p : Database::getUsers()) {
        str += (std::string) p + "\n";
    }
    return str; 
}

void Database::addFollowers(string username, string follower) {
    auto followedProfile = getUser(username);
    auto followerProfile = getUser(follower);
    followedProfile.addFollower(followerProfile);
    updateUser(username, followedProfile);
}

void Database::updateUser(string username, Profile newProfile) {
    users.at(username) = newProfile;
}
