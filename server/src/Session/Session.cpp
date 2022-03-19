#include <iostream>
#include "Session.h"

Session::Session(Profile *profile, Address address, unsigned int socketDescriptor, unsigned int sessionNum) :
        profile(profile),
        address(address),
        socketDescriptor(socketDescriptor),
        sessionNum(sessionNum),
        isOnlySession(false),
        isActive(false) {};

void Session::initSession() {
    start();
}


void Session::closeSession() {
    stop();
}


void Session::start() {
    isActive = true;
    producerThread = new thread(&Session::produce, this);
    consumerThread = new thread(&Session::consume, this);

    producerThread->detach();
    consumerThread->detach();
}

void Session::stop() {
    isActive = false;
}

void Session::consume() {
    std::unique_lock<mutex> lock(notificationsMutex);
    while (isActive) {
        conditionVariable.wait(lock, [this] { return !this->isActive || this->profile->hasPendingNotification(); });
        while (profile->hasPendingNotification()) {
            Notification notification = profile->getTopPendingNotification();
            if (isOnlySession) {
                profile->popPendingNotification();
                sendNotification(notification);
            } else {
                int assignedTo = profile->getTopPendingNotification().getLastReadBySession();
                if (assignedTo == this->sessionNum) {
                    sendNotification(notification);
                    if(assignedTo == 1)
                        profile->popPendingNotification();
                    else{
                        profile->markTopAsRead(this->sessionNum);
                    }
                }
            }
        }
    }
}

void Session::produce() {
    while (isActive) {
        {
            std::lock_guard<mutex> lock(notificationsMutex);

            while (profile->hasNotificationInBuffer()) {
                Notification notification = profile->popNotificationFromBuffer();
                for (auto follower: profile->getFollowers()) {
                    follower->addPendingNotification(notification);
                }
            }
        }
        conditionVariable.notify_all();
    }
    conditionVariable.notify_all();
}

void Session::setAsOnlySession() {
    isOnlySession = true;
}

void Session::unsetAsOnlySession() {
    isOnlySession = false;
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
