#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <errno.h>
#include "CommunicationManager.h"

#define MAXSIZE 1024

CommunicationManager::CommunicationManager(char* ipAddress, unsigned int port){
    this->ipAddress =ipAddress;
    this->port = port;
}

char* CommunicationManager::getIpAddress(){
    return this->ipAddress;
}

unsigned int CommunicationManager::getPort(){
    return this->port;
}

void CommunicationManager::runServer(){
    int socketDescriptor; //unique name identificator for socket
    //instanciate UDP socket
    if ( (socketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddress, clientAddress;
    memset(&clientAddress, 0, sizeof(clientAddress));
    memset(&serverAddress, 0, sizeof(serverAddress));

    // filling server information
    serverAddress.sin_family    = AF_INET; // ipv4 family
    serverAddress.sin_addr.s_addr = inet_addr(this->getIpAddress()); //converts port value to proper format
    serverAddress.sin_port = htons(this->getPort()); //converts ip to proper format
    unsigned int serverStructLength = sizeof(serverAddress);

    // Bind the socket with the server address
    if ( bind(socketDescriptor, (const struct sockaddr *)&serverAddress,
        sizeof(serverAddress)) < 0 ) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    char buffer[MAXSIZE];

    int len = sizeof(clientAddress);  //len is value/result

    recvfrom(socketDescriptor, buffer, MAXSIZE,
        MSG_WAITALL, (struct sockaddr*) &clientAddress,
        &serverStructLength);
    std::cout << "Client: " << buffer << std::endl;

    std::string response = "Hello from server";
    sendto(socketDescriptor, response.c_str(), response.length(),
        MSG_CONFIRM, (struct sockaddr*) &clientAddress,
        len);
    std::cout << "Response sent." << std::endl;

    //return 0;
}