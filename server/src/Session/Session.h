#pragma once

#include <netinet/in.h>
#include <utility>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "../Profile/Profile.h"
#include "../Notification/Notification.h"
#include "../Communication/CommunicationManager.h"

using std::pair;
using std::thread;
using std::mutex;
using std::condition_variable;
using std::lock_guard;

class Session {

public:
    Session(Profile *profile, Address address, unsigned int socketDescriptor, unsigned int sessionNum);

    void consume();

    void produce();

    Address getAddress();

    int getSessionNum();

    void initSession();

    void closeSession();

    void setAsOnlySession();

    void unsetAsOnlySession();

private:
    Profile *profile;
    Address address;

    mutex notificationsMutex;
    condition_variable conditionVariable;

    unsigned int sessionNum; //0 or 1, considering the 2 sessions limitation.
    volatile bool isOnlySession; //indicates if is the only active session
    unsigned int socketDescriptor;
    volatile bool isActive;

    thread *producerThread;
    thread *consumerThread;

    void sendNotification(Notification notification);

    void start();

    void stop();
};