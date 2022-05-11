#pragma once

#include "Session/ProfileSessionManager.h"
#include "Communication/CommunicationManager.h"
#include "Notification/Notification.h"
#include "Database/Database.h"

class Server {

private:
    bool isBackup;
    CommunicationManager communicationManager;

    void handlePacket(Packet packet, Address received);

public:
    Server(char *ipAddress, unsigned int port, 
        bool serverIsBackup, Address primaryServerAddress = {});
    void listen(int seqn, int64_t timestamp);
    void halt();
};
