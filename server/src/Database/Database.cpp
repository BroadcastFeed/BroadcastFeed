#include "Database.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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

        std::string user = section;
        addUser(user);

        while(std::getline(ss, section, ',')){
            std::string follower = section;

            if(!userExists(follower))
                addUser(follower); 
            addFollower(user, follower);
        }
    }
}

Database::~Database(){
    save();    
}

void Database::save(){
    std::ofstream fileOut;
    fileOut.open(FILENAME);

    std::string line;
    for(Profile user : getUsers()){
        line += user.getName() + ":";
        std::vector<Profile*> followers = user.getFollowers();
        for(auto it = followers.begin(); it != followers.end(); it++){
            if(it == followers.begin())
                line += (*it)->getName();
            else
                line += "," + (*it)->getName();
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
    if (!userExists(newUsername) && newUsername != "") {
        Profile newUser = Profile(newUsername);
        this->users.insert({newUsername, newUser});
    }
}

std::vector<Profile> Database::getUsers() const {
    vector<Profile> usersVector = {};
    for (std::pair<string, Profile> user : this->users) {
        usersVector.push_back(user.second);
    }

    return usersVector;
}

Profile* Database::getUser(const std::string& username){
    if (userExists(username)) { return &(this->users.at(username)); }
    else { return nullptr; }
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
    if (userExists(username)) { getUser(username)->addNotificationToProducerBuffer(notification); }
}


void Database::addFollower(const string& followedUsername, const string& followerUsername) {
    Profile* followedProfile = getUser(followedUsername);
    Profile* followerProfile = getUser(followerUsername);
    if (followedProfile != nullptr) {
        if (followerProfile != nullptr) { followedProfile->addFollower(followerProfile); }
    } else {
        std::cout << "User " << followedUsername << " doesnt exists!" << std::endl;
    }
}