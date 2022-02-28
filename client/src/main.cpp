#include "CommunicationManager.h"
#include "Interface.h"

#define MAXSIZE 1024

//for now the syntax is ./client <USERNAME> <IP ADDRESS> <PORT>

int main(int argc, char** argv) { 
    if (argc != 4) {
        exit(EXIT_FAILURE);
    }
    char* username = argv[1];
    char* ipAddress = argv[2];
    unsigned int port = atoi(argv[3]);
    
    Interface interface;
    interface.startSession(username);
    std::string message = interface.requestMessage();

    CommunicationManager communicationManager(ipAddress, port);
    communicationManager.initiateConnection(message);
}
