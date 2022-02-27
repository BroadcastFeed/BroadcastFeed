#include "Profile.h"

std::string Profile::getName(){
    return this.username;
}

void Profile::addFollower(Profile newFollower){
    this.followers.push_back(newFollower);
}