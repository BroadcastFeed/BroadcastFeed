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
    //instanciate UDP socket
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
    sendto(socketDescriptor, &packet, sizeof(packet),
        MSG_CONFIRM, (struct sockaddr*) &serverAddress,
        sizeof(serverAddress));
}

/*
char* CommunicationManager::getIpAddress(){
    return this->ipAddress;
}

unsigned int CommunicationManager::getPort(){
    return this->port;
}

void CommunicationManager::sendMessage(std::string message){

    int socketDescriptor; // unique name identificator for socket
    //instanciate UDP socket
    if ((socketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) {
        perror("Socket creation failed!");
        exit(EXIT_FAILURE);
    }
     
    struct sockaddr_in serverAddress; //instanciate socket address struct

    memset(&serverAddress, 0, sizeof(serverAddress)); 
    // filling server information
    serverAddress.sin_family = AF_INET; //ipv4 family
    serverAddress.sin_port = htons(port); //converts port value to proper format
    serverAddress.sin_addr.s_addr = inet_addr(ipAddress); //converts ip to proper format
    unsigned int serverStructLength = sizeof(serverAddress);

    char buffer[MAXSIZE] = "";

    if (sendto(socketDescriptor, message.data(), message.length(),
        MSG_CONFIRM, (struct sockaddr*) &serverAddress,
        sizeof(serverAddress)) < 0)
        std::cout << "Erro!";
    std::cout << "Message sent!" << std::endl;

    recvfrom(socketDescriptor, buffer, MAXSIZE,
        MSG_WAITALL, (struct sockaddr*) &serverAddress,
        &serverStructLength);
    std::cout << "Server: " << buffer << std::endl;

    close(socketDescriptor);
    //return 0;
}
*/





    
