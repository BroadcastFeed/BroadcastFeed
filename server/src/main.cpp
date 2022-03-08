#include <thread>
#include <signal.h>
#include <iostream>
#include <string>
#include <chrono>

#include "Communication/Packet.h"
#include "Server.h"

using namespace std::chrono;

int RUNNING = true;
Server* server;

//required by signal.h for ctrl-C handling
void handleCtrlC(int signal){
    RUNNING = false;
    server->halt();
}

//the syntax is ./server <IP ADDRESS> <PORT>
int main(int argc, char **argv) {

    //sets handleCtrlC as callback for SIGINT signals
    signal(SIGINT, handleCtrlC);

    if (argc != 3) {
        exit(EXIT_FAILURE);
    }
    char *ipAddress = argv[1];
    unsigned int port = atoi(argv[2]);

    server = new Server(ipAddress, port);

    int seqNum = 0;
    while (true) {
        int64_t timestampMillesseconds = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
        std::pair<Packet, Address> received = server.listen(seqNum, timestampMillesseconds);
//        server.handlePacket(received);
        std::cout << (std::string) received.first; //for debugging
        
        seqNum++;
    }
    std::cout << "\nExiting" << std::endl;
}
