#pragma once

#include <netinet/in.h>
#include <utility>
#include <thread>
#include "../Profile/Profile.h"
#include "../Notification/Notification.h"
#include "../Communication/CommunicationManager.h"

using std::pair;
using std::thread;
class Session {
    typedef sockaddr_in Address;

public:
    Session(Profile* profile, Address address, Address serverAddress, unsigned int socketDescriptor);
    void startThreads();
    ~Session();

    void consume();
    void produce();
    
    Address getAddress();

private:
    void sendNotification(Notification notification);

    Profile* profile;
    Address address;
    
    Address serverAddress;
    unsigned int socketDescriptor;

    bool isActive;

    thread* producerThread;
    thread* consumerThread;
};