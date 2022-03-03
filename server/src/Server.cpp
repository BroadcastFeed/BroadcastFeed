#include "Server.h"

Server::Server(char* ipAddress, unsigned int port) : communicationManager(ipAddress, port) {}

Packet Server::listen(){
    return this->communicationManager.listen();
}

Packet Server::putTimestamp(Packet packet, unsigned int timestamp){
    return this->communicationManager.putTimestamp(packet, timestamp);
}