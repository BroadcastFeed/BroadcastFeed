#include "Profile.h"

Profile::Profile(std::string username){
    this.username = username;
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