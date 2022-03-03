#include "CommunicationManager.h"
#include "Interface.h"
#include "Packet.h"

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
    
    int seqn = 0;
    while(true){
        std::string message = interface.requestMessage();
        CommunicationManager communicationManager(ipAddress, port);
        Packet packet = communicationManager.createPacket(message, seqn); //message for testing
        communicationManager.send(packet);
        seqn++;
    }
}
