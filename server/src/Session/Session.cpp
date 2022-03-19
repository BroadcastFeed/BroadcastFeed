#include <iostream>
#include "Session.h"

Session::Session(Profile *profile, Address address, unsigned int socketDescriptor, unsigned int sessionNum) :
        profile(profile),
        address(address),
        socketDescriptor(socketDescriptor),
        sessionNum(sessionNum),
        isOnlySession(false),
        isActive(false) {};

//Session::~Session() {
//    stop();
//}

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
    while (isActive) {
        std::unique_lock<mutex> lock(notificationsMutex);
        conditionVariable.wait(lock, [this] { return !this->isActive || this->profile->hasPendingNotification(); });
        while (profile->hasPendingNotification()) {
            Notification notification = profile->getTopPendingNotification();
            int lastRead = notification.getLastReadBySession();
            if (isOnlySession){
                profile->popPendingNotification();
                //if (lastRead == -1) 
                sendNotification(notification);
            } else {
                if (lastRead != this->sessionNum) {
                    profile->markTopAsRead(this->sessionNum);
                    if (lastRead != -1) {
                        profile->popPendingNotification();
                    }
                    sendNotification(notification);
                }
            }
        }
    }
}

void Session::produce() {
    while (isActive) {
        {
            std::lock_guard<mutex> lock(notificationsMutex);

            if (profile->hasNotificationInBuffer()) {
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

void Session::setAsOnlySession(){
    isOnlySession = true;
}

void Session::unsetAsOnlySession(){
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
