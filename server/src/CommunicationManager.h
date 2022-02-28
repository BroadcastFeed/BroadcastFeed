#include <string>
#include <netinet/in.h>

class CommunicationManager{
    private:
        unsigned int socketDescriptor;
        struct sockaddr_in serverAddress;
    public:
        CommunicationManager(char* ipAddress, unsigned int port);
        sockaddr_in acceptConnection();
        void handleConnection(sockaddr_in clientAddress);
};