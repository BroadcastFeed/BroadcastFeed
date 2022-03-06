#include "CommunicationManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <string>
#include <iostream>

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

std::pair<Packet, Address> CommunicationManager::listen(int seqn, int64_t timestamp) {
    unsigned int serverStructLength = sizeof(this->serverAddress);
    Address clientAddress;
    memset(&clientAddress, 0, sizeof(clientAddress));
    char buffer[MAXSIZE] = "";
    recvfrom(this->socketDescriptor, buffer, MAXSIZE,
             MSG_WAITALL, (struct sockaddr *) &clientAddress,
             &serverStructLength);
    Packet packet = Packet(buffer);
    packet.setTimestamp(timestamp);
    packet.setSeqNum(seqn);
    return std::pair(packet, clientAddress);
}

void CommunicationManager::handleConnection(Address clientAddress) {
    static std::string response = "Bem-vinde";
    sendto(socketDescriptor, response.c_str(), response.length(),
           MSG_CONFIRM, (struct sockaddr *) &clientAddress,
           sizeof(clientAddress));
    std::cout << response << std::endl;
}
