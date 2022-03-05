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
    CommunicationManager communicationManager(ipAddress, port);

    //std::string startMessage = 
    Packet startPacket = communicationManager.createPacket((std::string) "START "+ (std::string) username);
    communicationManager.send(startPacket);
    
    while(true){
        std::string message = interface.requestMessage();
        Packet packet = communicationManager.createPacket(message);
        communicationManager.send(packet);
    }
}
