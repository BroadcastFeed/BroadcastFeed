#include <stdexcept>
#include <signal.h>
#include "CommunicationManager.h"
#include "Interface.h"
#include "Packet.h"
#include "Tokenizer.h"

#define MAXSIZE 1024

int RUNNING = true;

void handleCtrlC(int s){
    RUNNING = false;
}

//for now the syntax is ./client <USERNAME> <IP ADDRESS> <PORT>
int main(int argc, char** argv) { 
    if (argc != 4) {
        exit(EXIT_FAILURE);
    }

    //sets handleCtrlC as callback for SIGINT signals
    signal(SIGINT, handleCtrlC);

    char* username = argv[1];
    char* ipAddress = argv[2];
    unsigned int port = atoi(argv[3]);
    
    CommunicationManager communicationManager(ipAddress, port);

    Interface interface;
    interface.startSession(username);

    Packet startPacket = Packet(PacketType::CONNECT, "", username);
    communicationManager.send(startPacket);
    
    std::string message;
    while(interface.requestMessage(message)) {
        try{
            PacketType type = tokenizeStringToParamType(message);
            Packet packet = Packet(type, message, username);
            communicationManager.send(packet);
        }
        catch(std::out_of_range){
            interface.commandNotFound();
        }
    }

    interface.exiting();
    Packet endPacket = Packet(PacketType::DISCONNECT, "", username);    
    communicationManager.send(endPacket);
}
