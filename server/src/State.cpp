#include "State.h"

void State::addUser(Profile newUser){
    this.users.push_back(newUser);
}

std::vector<Profile> State::getUsers(){
    return  this.users;
}