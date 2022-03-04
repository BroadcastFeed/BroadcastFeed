#include "Server.h"

Server::Server(char* ipAddress, unsigned int port) : communicationManager(ipAddress, port) {}

Packet Server::listen(int seqn, int64_t timestamp){
    return this->communicationManager.listen(seqn, timestamp);
}

void Server::handlePacket(Packet packet){
    if (packet.getType() == 1){
        //FOLLOW message
    }
    else if (packet.getType() == 2){
        //SEND message
    }
}

