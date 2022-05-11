#include <iostream>
#include "Server.h"

Server::Server(char *ipAddress, unsigned int port) 
: isPrimary(true), communicationManager(ipAddress, port) {}

Server::Server(char *ipAddress, unsigned int port, Address primaryServerAddress) 
: isPrimary(false), communicationManager(ipAddress, port), 
primaryServerAddress(primaryServerAddress) {
    communicationManager.connectAsBackupServer(primaryServerAddress);
}

void Server::listen(int seqn, int64_t timestamp) {
    std::pair<Packet, Address> received = this->communicationManager.listen(seqn, timestamp);
    std::cout << (string) ProfileSessionManager::getSessionsString() << std::endl;
    handlePacket(received.first, received.second);
}

void Server::handlePacket(Packet packet, Address address) {
    bool successful = false;
    switch (packet.getType()) {
        case CONNECT: {
            std::cout << "User " << packet.getUsername() << " requests to CONNECT" << std::endl;
            if(ProfileSessionManager::userCanConnect(packet.getUsername())) {
                successful = ProfileSessionManager::registerNewSession(
                        packet.getMessage(),
                        address,
                        communicationManager.getAddress(),
                        communicationManager.getDescriptor());
                communicationManager.sendAcknowledge(address);
            }
            break;
        }
        case SEND: {
            std::cout << "User " << packet.getUsername() << " requests to SEND: " << packet.getMessage() << std::endl;
            Notification notification(packet.getSeqNum(), packet.getTimestamp(),
                                      packet.getLength(), packet.getUsername(),
                                      packet.getMessage());
            successful = ProfileSessionManager::addNotification(packet.getUsername(), notification);
            communicationManager.sendAcknowledge(address);

            break;
        }

        case FOLLOW:
            std::cout << packet.getUsername() << " requests to FOLLOW: " << packet.getMessage() << std::endl;
            successful = ProfileSessionManager::addFollower(packet.getMessage(), packet.getUsername());
            communicationManager.sendAcknowledge(address);

            break;

        case DISCONNECT:
            std::cout << "User " << packet.getUsername() << " requests to DISCONNECT" << std::endl;
            successful = ProfileSessionManager::removeSession(packet.getUsername(), address);
            break;
            
        case CONNECT_BACKUP:
            std::cout << "New server CONNECTED AS BACKUP" << std::endl;
            serverAddresses.push_back(address);
            break;

        default:
            std::cout << "Command not found" << std::endl;
            communicationManager.sendAcknowledge(address);
            return;
    }
    if(successful){
        std::cout << "User " << packet.getUsername() << " request successful" << std::endl;
    }
}

void Server::halt() {
    shutdown(communicationManager.getDescriptor(), SHUT_RDWR);
}
