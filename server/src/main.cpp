#include <thread>
#include <iostream>
#include <string>

#include "Communication/Packet.h"
#include "Server.h"

//the syntax is ./server <IP ADDRESS> <PORT>

int main(int argc, char **argv) {
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }
    char *ipAddress = argv[1];
    unsigned int port = atoi(argv[2]);

    Server server(ipAddress, port);

    while (true) {
        Packet packet = server.listen();
        std::cout << (std::string) packet;
    }
}
