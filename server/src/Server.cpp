#include "Server.h"

Server::Server(char* ipAddress, unsigned int port) {
    CommunicationManager(ipAddress, port);
}