#pragma once

#include <vector>

#include "Notification/Notification.h"
#include "Database/Database.h"
#include "Session/ProfileSessionManager.h"
#include "Communication/CommunicationManager.h"
#include "Communication/Address.h"
#include "BackupManager.h"
#include "Interface.h"

class Server {

private:
    CommunicationManager communicationManager;
    void handlePacket(Packet packet, Address address);
    
    void checkPrimaryServer();
    void checkBackupNodes();

public:
    //construct primary server
    Server(char *ipAddress, unsigned int port);     
    //construct backup server
    Server(char *ipAddress, unsigned int port, Address primaryServerAddress);
    Server nextNode;

    bool isPrimary();
    void setAsPrimary();
    
    
    void listen(int seqn, int64_t timestamp);
    void startCheckingPrimary();
    void startCheckingBackups();

    void halt();
    void election();
};
