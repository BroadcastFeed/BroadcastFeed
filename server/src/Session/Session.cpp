#include "Session.h"

Session::Session(Profile& profile, Address address, CommunicationManager& communicationManager) 
: profile(profile), address(address), communicationManager(communicationManager){}

void Session::consume() {
    while(true){
        if(profile.hasNotificationToBeRead()){
            Notification notification = profile.popNotificationToBeRead();
            communicationManager.notify(notification, address); 
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

