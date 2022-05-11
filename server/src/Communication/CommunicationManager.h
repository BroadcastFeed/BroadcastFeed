#pragma once

#include <string>
#include "Packet.h"
#include "../Notification/Notification.h"
#include "Address.h"
#include <netinet/in.h>
#include <utility>

using std::string;

class CommunicationManager {
private:
    unsigned int socketDescriptor;
    Address serverAddress;

public:
    CommunicationManager(char *ipAddress, unsigned int port);

    std::pair<Packet, Address> listen(int seqn, int64_t timestamp);
    void sendAcknowledge(Address address);

    unsigned int getDescriptor();

    Address getAddress();
};