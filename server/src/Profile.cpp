#include "Profile.h"

Profile::Profile(std::string username){
    this.username = username;
    this.activeSessions = 0;
}

int Profile::getActiveSessions(){
    return this.activeSessions;
}

std::string Profile::getName(){
    return this.username;
}

std::vector<Profile> getFollowers(){
    return this.followers;
}

std::vector<Notification> getNotifications(){
    return this.notifications;
}

void Profile::addFollower(Profile newFollower){
    this.followers.push_back(newFollower);
}

void Profile::addNotification(Notification newNotification){
    this.notifications.push_back(newNotification);
}

Notification Profile::removeNotification(){ //assuming a queue implementation of the list
    Notification firstElement = this.notifications[0];
    this.notifications.erase(this.notifications.begin());
    return firstElement;
}

void startSession(){
    if (this.activeSessions < 2){ //otherwise, session is refused
        this.activeSessions++;
    }
}

void endSession(){
    if (this.activeSessions >0){
        this.activeSessions--;
    }
}