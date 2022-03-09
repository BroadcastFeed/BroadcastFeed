#include <iostream>
#include "Server.h"

Server::Server(char* ipAddress, unsigned int port) : communicationManager(ipAddress, port) {}

std::pair<Packet, Address> Server::listen(int seqn, int64_t timestamp){
    return this->communicationManager.listen(seqn, timestamp);
}

void Server::halt(){
    shutdown(communicationManager.getDescriptor(), SHUT_RDWR);
}
