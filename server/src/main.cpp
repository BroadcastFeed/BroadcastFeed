#include <thread>
#include <iostream>
#include <string>
#include <ctime>

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
        Packet inputPacket = server.listen();
        std::time_t timer = std::time(nullptr);
        Packet packet = server.putTimestamp(inputPacket, (unsigned int) timer);
        std::cout << (std::string) packet; //for debugging
    }
}
