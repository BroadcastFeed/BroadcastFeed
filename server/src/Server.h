#pragma once

#include "Session/ProfileSessionManager.h"
#include "Communication/CommunicationManager.h"
#include "Notification/NotificationManager.h"
#include "Notification/Notification.h"
#include "Database/Database.h"

class Server {

private:
    CommunicationManager communicationManager;
    NotificationManager notificationManager;
public:
    Server(char* ipAddress, unsigned int port);
    std::pair<Packet, Address> listen(int seqn, int64_t timestamp);
    void halt();
//    void handlePacket(std::pair<Packet, Address> received);
};
