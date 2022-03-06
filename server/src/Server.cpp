#include "Server.h"

Server::Server(char* ipAddress, unsigned int port) : communicationManager(ipAddress, port) {}

std::pair<Packet, Address> Server::listen(int seqn, int64_t timestamp){
    return this->communicationManager.listen(seqn, timestamp);
}

void Server::handlePacket(std::pair<Packet, Address> received){
    Packet packet = received.first;

    int pendingReaders = -1;
    Notification notification = Notification(0, 0, 0, 0, "");
    switch (packet.getType()) {
        case CONNECT:
            this->profileSessionManager.login(packet.getMessage());
            notification = Notification(packet.getSeqNum(), packet.getTimestamp(),
                                        packet.getLength(), pendingReaders,
                                        packet.getMessage());
            break;
        case SEND:
            pendingReaders = 0; //change later
            notification = Notification(packet.getSeqNum(), packet.getTimestamp(),
                                                     packet.getLength(), pendingReaders,
                                                     packet.getMessage());
            break;
        case FOLLOW:
            notification = Notification(packet.getSeqNum(), packet.getTimestamp(),
                                                     packet.getLength(), pendingReaders,
                                                     packet.getMessage());
            break;
        case DISCONNECT:
            notification = Notification(packet.getSeqNum(), packet.getTimestamp(),
                                        packet.getLength(), pendingReaders,
                                        packet.getMessage());
            break;
        default:
            notification = Notification(packet.getSeqNum(), packet.getTimestamp(),
                                        packet.getLength(), pendingReaders,
                                        packet.getMessage());
            return;
    }
}

