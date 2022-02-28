#include <string>

class CommunicationManager{
    private:
        char* ipAddress;
        unsigned int port;
    public:
        CommunicationManager(char* ipAddress, unsigned int port);
        char* getIpAddress();
        unsigned int getPort();
        void runServer();
};