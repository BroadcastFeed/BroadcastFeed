#include "Session.h"

Session::Session(Profile& profile, Address address, Address serverAddress, unsigned int socketDescriptor) 
: profile(profile), address(address), serverAddress(serverAddress), socketDescriptor(socketDescriptor) {}

void Session::consume() {
    while(true){
        if(profile.hasNotificationToBeRead()){
            Notification notification = profile.popNotificationToBeRead();
            sendNotification(notification); 
        }
    }
}

void Session::produce() {
    while(true){
        if(profile.hasNotificationToBeSent()){
            Notification notification = profile.popNotificationToBeSent();
            for(Profile& follower : profile.getFollowers()){
                follower.addNotificationToBeRead(notification);
            }
        }
    }
}

void Session::sendNotification(Notification notification){
    std::string message = notification.serialize();
    sendto(socketDescriptor, message.data(), message.length(),
        MSG_CONFIRM, (struct sockaddr*) &serverAddress,
        sizeof(serverAddress));
}

