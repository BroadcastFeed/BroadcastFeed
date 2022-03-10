#include "Database.h"
#include <string>
#include <fstream>
#include <sstream>

#define FILENAME "users.dat"

Database::Database(){
    std::ifstream fileIn;
    fileIn.open(FILENAME);
    
    std::string line;
    std::string section;
    while(fileIn){
        std::getline(fileIn, line);
        std::stringstream ss(line);
        std::getline(ss, section, ':');
        addUser(section);
        while(std::getline(ss, section, ',')){
            //add follower (section) to user
        }
    }
}

void Database::save(){
    std::ofstream fileOut;
    fileOut.open(FILENAME);

    std::string line;
    for(Profile user : users){
        line += user.getName() + ":";
        std::vector<Profile> followers;
        for(auto it = followers.begin(); it != followers.end(); it++){
            if(it == users.begin())
                line += it->getName();
            else
                line += "," + it->getName();
        }
        fileOut << line << std::endl;
        line = "";
    }
    fileOut.close();
}

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

void Database::addNotification(const string& username, const Notification& notification){
    auto userProfile = getUser(username);
    userProfile.addNotification(notification);
    updateUser(username, userProfile);
}

void Database::addFollower(const string& followedUsername, const string& followerUsername) {
    auto followedProfile = getUser(followedUsername);
    auto followerProfile = getUser(followerUsername);
    followedProfile.addFollower(followerProfile);
    updateUser(followedUsername, followedProfile);
}

void Database::updateUser(string username, Profile newProfile) {
    users.at(username) = newProfile;
}
