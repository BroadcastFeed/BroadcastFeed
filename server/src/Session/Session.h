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
    Session(Profile* profile, Address address, unsigned int socketDescriptor);
    ~Session();
    void consume();
    void produce();
    Address getAddress();

private:
    Profile* profile;
    Address address;


    unsigned int socketDescriptor;
    bool isActive;

    thread* producerThread;
    thread* consumerThread;

    void sendNotification(Notification notification);
    void startThreads();
};