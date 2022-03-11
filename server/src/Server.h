#pragma once

#include "Session/ProfileSessionManager.h"
#include "Communication/CommunicationManager.h"
#include "Notification/NotificationManager.h"
#include "Notification/Notification.h"
#include "Database/Database.h"
#include <thread>
#include <chrono>

using std::pair;
using std::move;
using std::thread;
using std::string;
using std::cout;
using std::endl;

class Server {

private:
    inline static map<thread::id, thread> openedThreads = {};
    inline static vector<thread> threads = {};
    CommunicationManager communicationManager;
    NotificationManager notificationManager;

    static void handlePacket(const Packet& packet, Address received);
public:
    Server(char* ipAddress, unsigned int port);
    void listen(int sequenceNumber, int64_t timestamp);
    void halt();
};
