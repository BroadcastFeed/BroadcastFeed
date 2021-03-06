#include "Profile.h"

#include <utility>

#include <iostream>

Profile::Profile(std::string username) {
    this->username = std::move(username);
    this->activeSessions = 0;
    this->notificationsQueueMutex = new mutex();
}

Profile::Profile() {
    this->notificationsQueueMutex = new mutex();
}

int Profile::getActiveSessions() {
    return this->activeSessions;
}

std::string Profile::getName() {
    return this->username;
}

std::vector<Profile *> Profile::getFollowers() {
    return this->followers;
}

std::vector<Notification> Profile::getProducerBuffer() {
    return this->producerBuffer;
}

Notification Profile::getTopPendingNotification() {
    std::lock_guard<mutex> lock(*(this->notificationsQueueMutex));
    return this->pendingNotifications[0];
}


void Profile::addFollower(Profile *newFollower) {
    this->followers.push_back(newFollower);
}

bool Profile::hasNotificationInBuffer() {
    return !producerBuffer.empty();
}

bool Profile::hasPendingNotification() {
    std::lock_guard<mutex> lock(*(this->notificationsQueueMutex));
    return !pendingNotifications.empty();
}


void Profile::addNotificationToProducerBuffer(const Notification &notification) {
    this->producerBuffer.push_back(notification);
}

void Profile::addPendingNotification(const Notification &notification) {
    std::lock_guard<mutex> lock(*(this->notificationsQueueMutex));
    this->pendingNotifications.push_back(notification);
    std::cout << (string) *this << std::endl;
}

void Profile::markTopAsRead() {
    std::lock_guard<mutex> lock(*(this->notificationsQueueMutex));
    pendingNotifications[0].markAsRead(1);
}

Notification Profile::popNotificationFromBuffer() { //assuming a queue implementation of the list
    Notification firstElement = this->producerBuffer[0];
    this->producerBuffer.erase(this->producerBuffer.begin());
    return firstElement;
}

Notification Profile::popPendingNotification() { //assuming a queue implementation of the list
    std::lock_guard<mutex> lock(*(this->notificationsQueueMutex));
    Notification firstElement = this->pendingNotifications[0];
    this->pendingNotifications.erase(this->pendingNotifications.begin());
    return firstElement;
}

Profile::operator std::string() const {
    std::string str;
    str += "Username: " + this->username + "\n";
    str += "Followers: " + std::to_string(this->followers.size()) + "\n";
    str += "Notifications to be sent: " + std::to_string(this->pendingNotifications.size()) + "\n";
    return str;
}

