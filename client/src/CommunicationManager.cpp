#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>
#include "CommunicationManager.h"

#define MAXSIZE 1024

CommunicationManager::CommunicationManager(char* ipAddress, unsigned int port){
    //instantiate UDP socket
    this->socketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if ( this->socketDescriptor  <  0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&(this->serverAddress), 0, sizeof(this->serverAddress));

    // filling server information
    this->serverAddress.sin_family    = AF_INET; // ipv4 family
    this->serverAddress.sin_addr.s_addr = inet_addr(ipAddress); 
    this->serverAddress.sin_port = htons(port); 
    
    this->running = false;
    listeningThread = new std::thread(&CommunicationManager::listen, this);
}

CommunicationManager::~CommunicationManager(){
    running = false;
    shutdown(socketDescriptor, SHUT_RDWR);
    listeningThread->join();
    delete(listeningThread);
}

void CommunicationManager::send(Packet packet){
    std::string message = packet.serialize();
    sendto(socketDescriptor, message.data(), message.length(),
        MSG_CONFIRM, (struct sockaddr*) &serverAddress,
        sizeof(serverAddress));
}

void CommunicationManager::startListening(){
    running = true;
}

void CommunicationManager::waitAcknowledge(){
    char buffer[MAXSIZE] = "";
    unsigned int serverStructLength = sizeof(this->serverAddress);
    bool waiting = true;
    while(waiting){
        recvfrom(
            this->socketDescriptor,
            buffer,
            MAXSIZE,
            MSG_WAITALL,
            (struct sockaddr*) &serverAddress,
            &serverStructLength
        );
        Packet receivedPacket(buffer);
        if(receivedPacket.getType() == ACKNOWLEDGE)
            waiting = false;
    }
}

void CommunicationManager::listen(){    
    while(running){
        char buffer[MAXSIZE] = "";
        unsigned int serverStructLength = sizeof(this->serverAddress);
        recvfrom(
            this->socketDescriptor, 
            buffer, 
            MAXSIZE,
            MSG_WAITALL, 
            (struct sockaddr *) &serverAddress,
            &serverStructLength
        );
        if(buffer != "" && running){
            Packet received(buffer);
            std::cout << std::endl << received.getUsername() << " says " << received.getMessage() << "\n> ";
            std::cout.flush();
        }
    }
}
