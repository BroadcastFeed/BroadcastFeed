#include <iostream>
#include "Server.h"

Server::Server(char* ipAddress, unsigned int port) : communicationManager(ipAddress, port) {}

void Server::listen(int seqn, int64_t timestamp){
    this->communicationManager.listen(seqn, timestamp);
}

void Server::handlePacket(Packet packet, Address received) {
    int pendingReaders = -1;
    Notification notification = Notification(0, 0, 0, 0, "");
    switch (packet.getType()) {
        case CONNECT: {
            std::pair<std::string, Address> session(packet.getMessage(), received);
//            this->profileSessionManager.registerNewSession(session);
//            notification = Notification(packet.getSeqNum(), packet.getTimestamp(),
//                                        packet.getLength(), pendingReaders,
//                                        packet.getMessage());
//            //DEBUG LINE FOR TESTING
//            std::cout << (std::string) profileSessionManager << std::endl;
            break;
        }
        case SEND:
            //pendingReaders = packet.getFollowers().length();
            notification = Notification(packet.getSeqNum(), packet.getTimestamp(),
                                        packet.getLength(), pendingReaders,
                                        packet.getMessage());
            ProfileSessionManager::addNotification(packet.getUsername(), notification);

            break;

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
