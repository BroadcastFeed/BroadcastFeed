#pragma once

#include <string>
#include "Packet.h"
#include "../Notification/Notification.h"
#include <netinet/in.h>
#include <utility>

using std::string;

typedef sockaddr_in Address;

class CommunicationManager {
private:
    unsigned int socketDescriptor;
    Address serverAddress;
    
    void sendPacket(Packet packet, Address destinationAddress);

public:
    CommunicationManager(char *ipAddress, unsigned int port);

    std::pair<Packet, Address> listen(int seqn, int64_t timestamp);
    void sendAcknowledge(Address address);
    void sendServerSwitchToClient(Address clientAddress);

    unsigned int getDescriptor();
    Address getAddress();
};