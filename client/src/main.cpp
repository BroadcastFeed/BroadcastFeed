#include <stdexcept>
#include <signal.h>
#include <iostream>
#include "CommunicationManager.h"
#include "Interface.h"
#include "Packet.h"
#include "Tokenizer.h"

#define MAXSIZE 1024

int RUNNING = true;

void handleInterruption(int signal){
    RUNNING = false;
}

//for now the syntax is ./client <USERNAME> <IP ADDRESS> <PORT>
int main(int argc, char** argv) { 
    if (argc != 4) {
        exit(EXIT_FAILURE);
    }

    struct sigaction sa = { sa.sa_handler = handleInterruption };

    //sets handleCtrlC as callback for SIGINT signals
    sigaction(SIGINT, &sa, 0);


    char* username = argv[1];
    char* ipAddress = argv[2];
    unsigned int port = atoi(argv[3]);
    
    CommunicationManager communicationManager(ipAddress, port);

    Interface interface;
    interface.startSession(username);

    Packet startPacket = Packet(PacketType::CONNECT, username, username);

    communicationManager.send(startPacket);
    interface.showWaitConnection();
    communicationManager.waitAcknowledge();
    interface.successfulConnection();
    communicationManager.startListening();
    
    std::string message;
    while(interface.requestMessage(message) && RUNNING) {
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
    Packet endPacket = Packet(PacketType::DISCONNECT, username, username);    
    communicationManager.send(endPacket);
}
