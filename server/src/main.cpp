#include <thread>
#include <iostream>
#include <string>

#include "Session/Packet.h"
#include "Communication/CommunicationManager.h"

//the syntax is ./server <IP ADDRESS> <PORT>

int main(int argc, char **argv) {
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }
    char *ipAddress = argv[1];
    unsigned int port = atoi(argv[2]);

    CommunicationManager communicationManager(ipAddress, port);
    while (true) {
        Packet packet = communicationManager.listen();
        std::cout << (std::string) packet;
    }
}
