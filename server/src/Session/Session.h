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
    Session(Profile* profile, Address address, unsigned int socketDescriptor, unsigned int sessionNum);
    ~Session();
    void consume();
    void produce();
    Address getAddress();
    int getSessionNum();

private:
    Profile* profile;
    Address address;

    unsigned int sessionNum; //1 or 2, considering the 2 sessions limitation.
    unsigned int socketDescriptor;
    bool isActive;

    thread* producerThread;
    thread* consumerThread;

    void sendNotification(Notification notification);
    void startThreads();
};