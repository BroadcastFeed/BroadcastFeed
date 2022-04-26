#include <iostream>
#include "Server.h"

Server::Server(char *ipAddress, unsigned int port) : communicationManager(ipAddress, port) {}

void Server::listen(int seqn, int64_t timestamp) {
    std::pair<Packet, Address> received = this->communicationManager.listen(seqn, timestamp);
    handlePacket(received.first, received.second);
}

void Server::handlePacket(Packet packet, Address received) {

    switch (packet.getType()) {
        case CONNECT: {
            std::cout << "User " << packet.getUsername() << " attempts to CONNECT" << std::endl;
            bool registered = ProfileSessionManager::registerNewSession(
                    packet.getMessage(),
                    received,
                    communicationManager.getAddress(),
                    communicationManager.getDescriptor());
            if (registered){
                std::cout << "User new session successfully connected" << std::endl;
                communicationManager.sendAcknowledge(received);
            }
            break;
        }
        case SEND: {
            std::cout << packet.getUsername() << " SEND: " << packet.getMessage() << std::endl;
            Notification notification(packet.getSeqNum(), packet.getTimestamp(),
                                      packet.getLength(), packet.getUsername(),
                                      packet.getMessage());
            ProfileSessionManager::addNotification(packet.getUsername(), notification);

            break;
        }

        case FOLLOW:
            std::cout << packet.getUsername() << " FOLLOWED: " << packet.getMessage() << std::endl;
            ProfileSessionManager::addFollower(packet.getMessage(), packet.getUsername());

            break;

        case DISCONNECT:
            std::cout << "User " << packet.getUsername() << " attempts to DISCONNECT" << std::endl;
            if (ProfileSessionManager::removeSession(packet.getUsername(), received))
                std::cout << "User DISCONNECTED, now has "
                          << ProfileSessionManager::getOpenedSessions(packet.getUsername()).size()
                          << " sessions" << std::endl;
            break;

        default:
            std::cout << "Command not found" << std::endl;
            return;
    }
}

void Server::halt() {
    shutdown(communicationManager.getDescriptor(), SHUT_RDWR);
}
