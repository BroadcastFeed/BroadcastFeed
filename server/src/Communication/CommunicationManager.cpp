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
    if (
            recvfrom(this->socketDescriptor, buffer, MAXSIZE,
                     MSG_WAITALL, (struct sockaddr *) &clientAddress,
                     &serverStructLength)
            <= 0) {
        throw std::runtime_error("Error getting packet");
    }
    Packet packet = Packet(buffer);
    packet.setTimestamp(timestamp);
    packet.setSeqNum(seqn);
    return std::pair(packet, clientAddress);
}

void CommunicationManager::sendPacket(Packet packet, Address destinationAddress) {
    std::string message = packet.serialize();
    sendto(this->socketDescriptor, message.data(), message.length(),
        MSG_CONFIRM, (struct sockaddr*) &destinationAddress,
        sizeof(destinationAddress));
}

void CommunicationManager::sendAcknowledge(Address clientAddress) {
    Packet ackPacket = Packet(PacketType::ACKNOWLEDGE, "", ""); //add username later
    sendPacket(ackPacket, clientAddress);
}

void CommunicationManager::sendServerSwitchToClient(Address clientAddress) {
    Packet serverSwitchPacket = Packet(PacketType::SERVER_SWITCH, "", "");
    sendPacket(serverSwitchPacket, clientAddress);
}


unsigned int CommunicationManager::getDescriptor() {
    return socketDescriptor;
}

Address CommunicationManager::getAddress() {
    return serverAddress;
}