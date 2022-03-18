#include "Session.h"

Session::Session(Profile *profile, Address address, unsigned int socketDescriptor, unsigned int sessionNum) :
        profile(profile),
        address(address),
        socketDescriptor(socketDescriptor),
        sessionNum(sessionNum),
        isActive(false) {
    startThreads();
}

Session::~Session() {
    if (isActive) {
        isActive = false;
        producerThread->join();
        consumerThread->join();
    }
}

void Session::startThreads() {
    isActive = true;
    producerThread = new thread(&Session::produce, this);
    consumerThread = new thread(&Session::consume, this);
}

void Session::consume() {
    while (isActive) {
        std::unique_lock<mutex> lock(notificationsMutex);
        conditionVariable.wait(lock, [this] { return this->profile->hasNotificationToBeRead(); });

        Notification notification = profile->getTopNotification();
        int lastRead = notification.getLastReadBySession();

        if (lastRead != this->sessionNum) {
            profile->markTopAsRead(this->sessionNum);
            if (lastRead != -1) {
                Notification _ = profile->popNotificationToBeRead();
            }
            sendNotification(notification);
        }
    }
}

void Session::produce() {
    while (isActive) {
        {
            std::lock_guard<mutex> lock(notificationsMutex);

            if (profile->hasNotificationToBeSent()) {
                Notification notification = profile->popNotificationToBeSent();
                for (auto follower: profile->getFollowers()) {
                    follower->addNotificationToBeRead(notification);
                }
            }
        }
        conditionVariable.notify_all();
    }
}

void Session::sendNotification(Notification notification) {
    std::string message = notification.serialize();
    sendto(socketDescriptor, message.data(), message.length(),
           MSG_CONFIRM, (struct sockaddr *) &address,
           sizeof(address));
}

Address Session::getAddress() {
    return address;
}

int Session::getSessionNum() {
    return this->sessionNum;
}