#include "CommunicationManager.h"
#include <sys/socket.h>
 #include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <errno.h>

#define MAXSIZE 1024

CommunicationManager::CommunicationManager(char *ipAddress, unsigned int port) {
    //instanciate UDP socket
    this->socketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (this->socketDescriptor < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&(this->serverAddress), 0, sizeof(this->serverAddress));

    // filling server information
    this->serverAddress.sin_family = AF_INET; // ipv4 family
    this->serverAddress.sin_addr.s_addr = inet_addr(ipAddress);
    this->serverAddress.sin_port = htons(port);

    // Bind the socket with the server address
    if (bind(socketDescriptor, (const struct sockaddr *) &(this->serverAddress),
             sizeof(this->serverAddress)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

Packet CommunicationManager::listen() {
    unsigned int serverStructLength = sizeof(this->serverAddress);
    struct sockaddr_in clientAddress;
    memset(&clientAddress, 0, sizeof(clientAddress));
    char buffer[MAXSIZE] = "";
    recvfrom(this->socketDescriptor, buffer, MAXSIZE,
             MSG_WAITALL, (struct sockaddr *) &clientAddress,
             &serverStructLength);
    return Packet(buffer);
}

Packet CommunicationManager::putTimestamp(Packet packet, unsigned int timestamp) {
    return Packet(packet.getType(), packet.getSeqNum(), packet.getLength(), timestamp, packet.getMessage());
}

void CommunicationManager::handleConnection(sockaddr_in clientAddress) {
    static std::string response = "Bem-vinde";
    sendto(socketDescriptor, response.c_str(), response.length(),
           MSG_CONFIRM, (struct sockaddr *) &clientAddress,
           sizeof(clientAddress));
    std::cout << response << std::endl;
}
