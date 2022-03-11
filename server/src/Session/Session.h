#pragma once

#include <netinet/in.h>
#include "../Profile/Profile.h"
#include "../Notification/Notification.h"
#include "../Communication/CommunicationManager.h"

class Session {
    typedef sockaddr_in Address;

public:
    Session(Profile& profile, Address address, CommunicationManager& communicationManager);
    void consume();
    void produce();

private:
    void sendNotification(Notification notification, Address address);

    Profile& profile;
    Address address;
    CommunicationManager& communicationManager;
};