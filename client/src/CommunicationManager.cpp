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
}

void CommunicationManager::send(Packet packet){
    std::string message = packet.serialize();
    sendto(socketDescriptor, message.data(), message.length(),
        MSG_CONFIRM, (struct sockaddr*) &serverAddress,
        sizeof(serverAddress));
}

Packet CommunicationManager::createPacket(std::string message){
    /*packet type convention:
        1 - START (session) messages
        2 - FOLLOW messages
        3 - SEND messages
        else - INVALID TYPE
    */

    int type = -1;
    if (message.rfind("START ", 0) == 0){
        type = 1;
        message.erase(0,6);
    }
    else if (message.rfind("FOLLOW ", 0) == 0){
        type = 2;
        message.erase(0,7);
    }
    else if (message.rfind("SEND ", 0) == 0){
        type = 3;
        message.erase(0,5);
    }

    int length = message.length();
    int timestamp = -1;
    int seqn = -1; 

    return Packet(type, seqn, length, timestamp, message);

}
