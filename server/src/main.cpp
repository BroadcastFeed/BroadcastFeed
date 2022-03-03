#include <thread>
#include <iostream>
#include <string>
#include <time.h>

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
    time_t timer;

    while (true) {
        Packet inputPacket = server.listen();
        timer = time(NULL);
        Packet packet = server.putTimestamp(inputPacket, (float) timer);
        std::cout << (std::string) packet; //for debugging
    }
}
