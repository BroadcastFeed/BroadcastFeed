#include <stdexcept>
#include <iostream>
#include "CommunicationManager.h"
#include "Interface.h"
#include "Packet.h"
#include "Tokenizer.h"

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

    Packet startPacket = Packet(PacketType::CONNECT, username, username);
    communicationManager.send(startPacket);
    
    while(true) {
        std::string message = interface.requestMessage();
        try{
            PacketType type = tokenizeStringToParamType(message);
            Packet packet = Packet(type, message, username);
            communicationManager.send(packet);
        }
        catch(std::out_of_range){
            interface.commandNotFound();
        }
    }
}
