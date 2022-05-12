#pragma once

#include <vector>

#include "Session/ProfileSessionManager.h"
#include "Communication/CommunicationManager.h"
#include "Notification/Notification.h"
#include "Database/Database.h"

class Server {

private:
    bool isPrimary;
    vector<Address> serverAddresses; 
    Address primaryServerAddress;
    
    CommunicationManager communicationManager;
    void handlePacket(Packet packet, Address address);

public:
    //construct primary server
    Server(char *ipAddress, unsigned int port);     
    //construct backup server
    Server(char *ipAddress, unsigned int port, Address primaryServerAddress);

    void listen(int seqn, int64_t timestamp);
    void checkConnection(char *ipAddress, unsigned int port) {
        std::thread pingThread([this, ipAddress, port] {
            Address address = CommunicationManager::createDestinationAddress(ipAddress, port);
            bool reachable = this->communicationManager.isReachable(address);
            std::cout << address << " reachability " << reachable << std::endl;
        });
        pingThread.detach();
    }

    void halt();
};
