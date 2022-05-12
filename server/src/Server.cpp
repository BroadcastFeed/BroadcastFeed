#include <iostream>

#include "Server.h"
#include "Communication/ServerPingService.h"

Server::Server(char *ipAddress, unsigned int port)
        : communicationManager(ipAddress, port) {
    BackupManager::setServerAsPrimary();
    Interface::serverStart(isPrimary());
}

Server::Server(char *ipAddress, unsigned int port, Address primaryServerAddress)
        : communicationManager(ipAddress, port) {
    Interface::serverStart(isPrimary());
    BackupManager::setPrimaryServerAddress(primaryServerAddress);
    communicationManager.connectAsBackupServer(primaryServerAddress);
}

bool Server::isPrimary() {
    return BackupManager::isPrimaryServer();
}

void Server::setAsPrimary() {
    BackupManager::setServerAsPrimary();
}

void Server::listen(int seqn, int64_t timestamp) {
    std::pair<Packet, Address> received = this->communicationManager.listen(seqn, timestamp);
    handlePacket(received.first, received.second);
}

void Server::handlePacket(Packet packet, Address address) {
    bool successful = false;
    Interface::informReceivedPacket(packet, address, isPrimary());
    switch (packet.getType()) {
        case CONNECT: {
            if (ProfileSessionManager::userCanConnect(packet.getUsername())) {
                successful = ProfileSessionManager::registerNewSession(
                        packet.getUsername(),
                        address,
                        CommunicationManager::serverAddress,
                        CommunicationManager::socketDescriptor,
                        isPrimary());
                communicationManager.sendAcknowledge(address);
            }
            break;
        }
        case SEND: {
            Notification notification(packet.getSeqNum(), packet.getTimestamp(),
                                      packet.getLength(), packet.getUsername(),
                                      packet.getMessage());
            successful = ProfileSessionManager::addNotification(packet.getUsername(), notification);
            communicationManager.sendAcknowledge(address);

            break;
        }

        case FOLLOW:
            successful = ProfileSessionManager::addFollower(packet.getMessage(), packet.getUsername());
            communicationManager.sendAcknowledge(address);

            break;

        case DISCONNECT:
            successful = ProfileSessionManager::removeSession(packet.getUsername(), address);
            break;

        case NOTIFICATION:
            if (!isPrimary()) {
                ProfileSessionManager::popNotification(packet.getUsername());
                communicationManager.sendAcknowledge(address);
            }
            break;

        case CONNECT_BACKUP:
            BackupManager::newBackupServer(address);
            break;

        case ACKNOWLEDGE:
            //do something
            break;


        case PING:
            communicationManager.sendPong(address);
            break;

        case PONG:
            communicationManager.receivePong(address);
            break;

        default:
            std::cout << "Command not found" << std::endl;
            communicationManager.sendAcknowledge(address);
            return;
    }
    if (successful && isPrimary()) {
        Interface::informSuccessfulRequest(packet);
        BackupManager::replicateToBackups(packet);
    }
}

void Server::halt() {
    shutdown(CommunicationManager::socketDescriptor, SHUT_RDWR);
}

void Server::election() {
    std::cout << "Not implemented yet" << std::endl;
}

void Server::startCheckingPrimary(int frequency) {
    ServerPingService serverPingService(communicationManager, *this);
    serverPingService.startCheckingPrimary(frequency);
}

void Server::startCheckingBackups(int frequency) {
    ServerPingService serverPingService(communicationManager, *this);
    serverPingService.startCheckingBackups(frequency);
}
