#pragma once
#include <string>
#include <netinet/in.h>

#include "Packet.h"

class CommunicationManager{
    private:
        unsigned int socketDescriptor;
        struct sockaddr_in serverAddress{};
        

    public:
        CommunicationManager(char* ipAddress, unsigned int port);
        void send(Packet packet);
        Packet createPacket(PacketType type, std::string message);
};