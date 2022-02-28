#include <netinet/in.h>
#include "CommunicationManager.h"

//the syntax is ./server <IP ADDRESS> <PORT>

int main(int argc, char** argv) { 
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }
    char* ipAddress = argv[1];
    unsigned int port = atoi(argv[2]);
    
    CommunicationManager communicationManager(ipAddress, port);
    sockaddr_in clientAddress = communicationManager.acceptConnection();
    communicationManager.handleConnection(clientAddress);
}
