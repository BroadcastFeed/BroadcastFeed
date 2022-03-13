#include "Session.h"

Session::Session(Profile* profile, Address address, Address serverAddress, unsigned int socketDescriptor) : 
    profile(profile), 
    address(address), 
    serverAddress(serverAddress), 
    socketDescriptor(socketDescriptor),
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
            Notification notification = profile->popNotificationToBeRead();
            sendNotification(notification); 
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
