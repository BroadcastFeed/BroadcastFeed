#include "State.h"

void State::addUser(std::string newUsername){
    bool alreadyExists = false;
    for (auto & profile : this->users){
        if (newUsername == profile.getName()){
            alreadyExists = true;
        }
    }
    if (!alreadyExists){
        Profile newUser = Profile(newUsername);
        this->users.push_back(newUser);   
    }
}

std::vector<Profile> State::getUsers(){
    return  this->users;
}