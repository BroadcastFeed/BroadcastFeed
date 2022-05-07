#include <iostream>
#include "Server.h"

Server::Server(char *ipAddress, unsigned int port) : communicationManager(ipAddress, port) {}

void Server::listen(int seqn, int64_t timestamp) {
    std::pair<Packet, Address> received = this->communicationManager.listen(seqn, timestamp);
    handlePacket(received.first, received.second);
}

void Server::handlePacket(Packet packet, Address received) {
    bool successful = false;

    switch (packet.getType()) {
        case CONNECT: {
            std::cout << "User " << packet.getUsername() << " requests to CONNECT" << std::endl;
            successful = ProfileSessionManager::registerNewSession(
                    packet.getMessage(),
                    received,
                    communicationManager.getAddress(),
                    communicationManager.getDescriptor());
            break;
        }
        case SEND: {
            std::cout << "User " << packet.getUsername() << " attempts to SEND: " << packet.getMessage() << std::endl;
            Notification notification(packet.getSeqNum(), packet.getTimestamp(),
                                      packet.getLength(), packet.getUsername(),
                                      packet.getMessage());
            successful = ProfileSessionManager::addNotification(packet.getUsername(), notification);

            break;
        }

        case FOLLOW:
            std::cout << packet.getUsername() << " FOLLOWED: " << packet.getMessage() << std::endl;
            successful = ProfileSessionManager::addFollower(packet.getMessage(), packet.getUsername());

            break;

        case DISCONNECT:
            std::cout << "User " << packet.getUsername() << " attempts to DISCONNECT" << std::endl;
            successful = ProfileSessionManager::removeSession(packet.getUsername(), received);
            break;

        default:
            std::cout << "Command not found" << std::endl;
            return;
    }

    communicationManager.sendAcknowledge(received);
    if(successful){
        std::cout << "User " << packet.getUsername() << " request successful" << std::endl;
    }
}

void Server::halt() {
    shutdown(communicationManager.getDescriptor(), SHUT_RDWR);
}
