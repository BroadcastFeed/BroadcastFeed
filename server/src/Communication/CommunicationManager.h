#pragma once

#include <string>
#include "Packet.h"
#include <netinet/in.h>

using std::string;

class CommunicationManager {
private:
    unsigned int socketDescriptor;
    struct sockaddr_in serverAddress;
public:
    CommunicationManager(char *ipAddress, unsigned int port);

    Packet listen();

    void handleConnection(sockaddr_in clientAddress);
};