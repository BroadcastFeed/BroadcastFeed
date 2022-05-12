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
    Server nextNode();

    void handlePacket(Packet packet, Address address);

public:
    //construct primary server
    Server(char *ipAddress, unsigned int port);     
    //construct backup server
    Server(char *ipAddress, unsigned int port, Address primaryServerAddress);


    bool isPrimary();
    void setAsPrimary();
    
    
    void listen(int seqn, int64_t timestamp);
    void startCheckingPrimary(int frequency);
    void startCheckingBackups(int frequency);

    void halt();
    void election();
};
