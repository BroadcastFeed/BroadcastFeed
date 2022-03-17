#include "Profile.h"

Profile::Profile(std::string username) {
    this->username = username;
    this->activeSessions = 0;
}

Profile::Profile(){}

int Profile::getActiveSessions() {
    return this->activeSessions;
}

std::string Profile::getName() {
    return this->username;
}

std::vector<Profile*> Profile::getFollowers() {
    return this->followers;
}

std::vector<Notification> Profile::getNotificationsToBeSent() {
    return this->notificationsToBeSent;
}

void Profile::addFollower(Profile* newFollower) {
    this->followers.push_back(newFollower);
}

bool Profile::hasNotificationToBeSent() {
    return !notificationsToBeSent.empty();
}

bool Profile::hasNotificationToBeRead() {
    return !notificationsToBeRead.empty();
}


void Profile::addNotificationToBeSent(Notification notification) {
    this->notificationsToBeSent.push_back(notification);
}

void Profile::addNotificationToBeRead(Notification notification) {
    this->notificationsToBeRead.push_back(notification);
}

Notification Profile::popNotificationToBeSent() { //assuming a queue implementation of the list
    Notification firstElement = this->notificationsToBeSent[0];
    this->notificationsToBeSent.erase(this->notificationsToBeSent.begin());
    return firstElement;
}

Notification Profile::popNotificationToBeRead() { //assuming a queue implementation of the list
    Notification firstElement = this->notificationsToBeRead[0];
    this->notificationsToBeRead.erase(this->notificationsToBeRead.begin());
    return firstElement;
}

Profile::operator std::string() const { 
    std::string str;
    str += "Username: " + this->username + "\n";    
    str += "Followers: " + std::to_string(this->followers.size()) + "\n";
    str += "Notifications to be sent: " + std::to_string(this->notificationsToBeSent.size()) + "\n";
    return str; 
}