#include "Session.h"

Session::Session(Profile* profile, Address address, unsigned int socketDescriptor, unsigned int sessionNum): 
    profile(profile), 
    address(address), 
    socketDescriptor(socketDescriptor),
    sessionNum(sessionNum),
    isActive(false)
    {
        startThreads();
    }

Session::~Session(){
    if(isActive){
        isActive = false;
        producerThread->join();
        consumerThread->join();
    }
}

void Session::startThreads(){
    isActive = true;
    producerThread = new thread(&Session::produce, this);    
    consumerThread = new thread(&Session::consume, this);    
}

void Session::consume() {
    while(isActive){
        if(profile->hasNotificationToBeRead()){
            //Notification notification = profile->popNotificationToBeRead();
            Notification notification = profile->getTopNotification();
            bool isRead = false;
            int sum = 0;
            for (auto sessionNumber: notification.getReadBySessions()){
                if(sessionNumber==this->sessionNum){
                    isRead = true;
                }
                sum = sum + sessionNumber;
            }
            if(!isRead){ //my ugliest piece of code in a while
                profile->markTopAsRead(this->sessionNum);
                if(sum == 3){ //sessions 1 and 2 have already read.
                    Notification _ = profile->popNotificationToBeRead();
                }
                sendNotification(notification); 
            }
        }
    }
}

void Session::produce() {
    while(isActive){
        if(profile->hasNotificationToBeSent()){
            Notification notification = profile->popNotificationToBeSent();
            for(auto follower : profile->getFollowers()){
                follower->addNotificationToBeRead(notification);
            }
        }
    }
}

void Session::sendNotification(Notification notification){
    std::string message = notification.serialize();
    sendto(socketDescriptor, message.data(), message.length(),
        MSG_CONFIRM, (struct sockaddr*) &address,
        sizeof(address));
}

Address Session::getAddress(){
    return address;
}

int Session::getSessionNum(){
    return this->sessionNum;
}