#include <thread>
#include <iostream>
#include <string>
#include <chrono>

#include "Communication/Packet.h"
#include "Server.h"

using namespace std::chrono;

//the syntax is ./server <IP ADDRESS> <PORT>

int main(int argc, char **argv) {
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }
    char *ipAddress = argv[1];
    unsigned int port = atoi(argv[2]);

    Server server(ipAddress, port);

    int seqNum = 0;
    while (true) {
        milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
        Packet packet = server.listen(seqNum, ms.count());
        server.handlePacket(packet);
        std::cout << (std::string) packet; //for debugging
        seqNum++;
    }
}
