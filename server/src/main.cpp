#include <netinet/in.h>
#include <thread>
#include "CommunicationManager.h"

//the syntax is ./server <IP ADDRESS> <PORT>

int main(int argc, char** argv) { 
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }
    char* ipAddress = argv[1];
    unsigned int port = atoi(argv[2]);
    
    CommunicationManager communicationManager(ipAddress, port);
    while(true){
        sockaddr_in clientAddress = communicationManager.listen();
        std::thread clientThread(&CommunicationManager::handleConnection,communicationManager,clientAddress);
        clientThread.join();
    }
}
