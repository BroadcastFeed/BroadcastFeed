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

public:
    CommunicationManager(char *ipAddress, unsigned int port);

    std::pair<Packet, Address> listen(int seqn, int64_t timestamp);

    unsigned int getDescriptor();

    Address getAddress();
};