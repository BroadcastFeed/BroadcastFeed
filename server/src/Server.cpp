#include <iostream>
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
        case CONNECT:{
            std::pair<std::string, Address> session(packet.getMessage(), received.second); 
            this->profileSessionManager.login(session);
            notification = Notification(packet.getSeqNum(), packet.getTimestamp(),
                                        packet.getLength(), pendingReaders,
                                        packet.getMessage());
            //DEBUG LINE FOR TESTING
            std::cout << (std::string) profileSessionManager << std::endl;
            break;
        }
        case SEND:
            pendingReaders = 0; //change later
            notification = Notification(packet.getSeqNum(), packet.getTimestamp(),
                                                     packet.getLength(), pendingReaders,
                                                     packet.getMessage());
            break;
            
        case FOLLOW:

            break;

        case DISCONNECT:

            break;

        default:

            return;
    }
}

