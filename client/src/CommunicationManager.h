#pragma once
#include <string>
#include <thread>
#include <netinet/in.h>

#include "Packet.h"

class CommunicationManager{
    private:
        unsigned int socketDescriptor;
        struct sockaddr_in serverAddress{};

        std::thread* listeningThread;
        bool running = false;
        
        void listen();

        

    public:
        CommunicationManager(char* ipAddress, unsigned int port);
        ~CommunicationManager();
        void send(Packet packet);
        void startListening();
};