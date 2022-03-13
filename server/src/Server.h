#pragma once

#include "Session/ProfileSessionManager.h"
#include "Communication/CommunicationManager.h"
#include "Notification/Notification.h"
#include "Database/Database.h"

class Server {

private:
    CommunicationManager communicationManager;

    void handlePacket(Packet packet, Address received);
public:
    Server(char* ipAddress, unsigned int port);
    void listen(int seqn, int64_t timestamp);
    void halt();
};
