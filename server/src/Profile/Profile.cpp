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

std::vector<Profile> Profile::getFollowers() {
    return this->followers;
}

std::vector<Notification> Profile::getPendingNotifications() {
    return this->pendingNotifications;
}

void Profile::addFollower(Profile newFollower) {
    this->followers.push_back(newFollower);
}

void Profile::addNotification(Notification newNotification) {
    this->pendingNotifications.push_back(newNotification);
}

Notification Profile::removeNotification() { //assuming a queue implementation of the list
    Notification firstElement = this->pendingNotifications[0];
    this->pendingNotifications.erase(this->pendingNotifications.begin());
    return firstElement;
}

void Profile::startSession() {
    if (this->activeSessions < 2) { //otherwise, session is refused
        this->activeSessions++;
    }
}

void Profile::endSession() {
    if (this->activeSessions > 0) {
        this->activeSessions--;
    }
}

Profile::operator std::string() const { 
    std::string str;
    str += "Username: " + this->username + "\n";    
    str += "Followers: " + std::to_string(this->followers.size()) + "\n";
    str += "Pending Notifications: " + std::to_string(this->pendingNotifications.size()) + "\n";
    return str; 
}