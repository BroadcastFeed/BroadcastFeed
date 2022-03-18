#include <iostream>
#include "Session.h"

Session::Session(Profile *profile, Address address, unsigned int socketDescriptor, unsigned int sessionNum) :
        profile(profile),
        address(address),
        socketDescriptor(socketDescriptor),
        sessionNum(sessionNum),
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

            if (lastRead != this->sessionNum) {
                profile->markTopAsRead(this->sessionNum);
                if (lastRead != -1) {
                    Notification _ = profile->popPendingNotification();
                }
                sendNotification(notification);
            }
        }
    }
//    std::cout << "CONSUMER: I'm about to die" << std::endl;
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
//    std::cout << "PRODUCER: I'm about to die" << std::endl;
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