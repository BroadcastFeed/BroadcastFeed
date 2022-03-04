#pragma once

#include "Session/ProfileSessionManager.h"
#include "Communication/CommunicationManager.h"
#include "Notification/NotificationManager.h"
#include "Database/Database.h"

class Server {

private:
    CommunicationManager communicationManager = CommunicationManager(nullptr, 0);
    Database database;
    NotificationManager notificationManager;
    ProfileSessionManager profileSessionManager;
public:
    Server(char* ipAddress, unsigned int port);
    Packet listen(int seqn, int64_t timestamp);
};
