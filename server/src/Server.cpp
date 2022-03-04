#include "Server.h"

Server::Server(char* ipAddress, unsigned int port) : communicationManager(ipAddress, port) {}

Packet Server::listen(){
    return this->communicationManager.listen();
}

Packet Server::putTimestamp(Packet packet, int64_t timestamp){
    return this->communicationManager.putTimestamp(packet, timestamp);
}