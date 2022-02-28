#pragma once
#include <string>

class CommunicationManager{
    private:
        char* username;
        char* ipAddress;
        unsigned int port;

    public:
        CommunicationManager(char* ipAddress, unsigned int port);
        char* getUsername();
        char* getIpAddress();
        unsigned int getPort();
        void sendMessage(std::string message);
};