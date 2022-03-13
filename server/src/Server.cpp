#include <iostream>
#include <thread>
#include "Server.h"

Server::Server(char* ipAddress, unsigned int port) : communicationManager(ipAddress, port) {}

void Server::listen(int seqn, int64_t timestamp){
    std::pair<Packet, Address> received =  this->communicationManager.listen(seqn, timestamp);
    handlePacket(received.first, received.second);
}

void Server::handlePacket(Packet packet, Address received) {
    int pendingReaders = -1;
    switch (packet.getType()) {
        case CONNECT: {
            ProfileSessionManager::registerNewSession(
                packet.getMessage(), 
                received, 
                communicationManager.getAddress(),
                communicationManager.getDescriptor());
            break;
        }
        case SEND: {
            //pendingReaders = packet.getFollowers().length();
            Notification notification(packet.getSeqNum(), packet.getTimestamp(),
                                        packet.getLength(), pendingReaders, packet.getUsername(),
                                        packet.getMessage());
            ProfileSessionManager::addNotification(packet.getUsername(), notification);

            break;
        }

        case FOLLOW:
            ProfileSessionManager::addFollower(packet.getMessage(), packet.getUsername());

            break;

        case DISCONNECT:

            break;

        default:

            return;
    }
}

void Server::halt(){
    shutdown(communicationManager.getDescriptor(), SHUT_RDWR);
}
