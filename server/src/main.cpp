#include <thread>
#include <signal.h>
#include <iostream>
#include <string>
#include <chrono>
#include <cstring>

#include <arpa/inet.h> 

#include "Server.h"

using namespace std::chrono;

int RUNNING = true;
Server *server;

void handleInterruption(int signal) {
    RUNNING = false;
    server->halt();
}

// Usage:
//   ./server <IP ADDRESS> <PORT> [optional: <PRIMARY IP ADDRESS> <PRIMARY PORT>]
//
//   When given the optional arguments <PRIMARY IP ADDRESS> and <PRIMARY PORT>
//   the server will start as a backup to the primary server 
//   specified in the address.

int main(int argc, char **argv) {
    if (argc < 3 || argc > 5 || argc == 4) {
        exit(EXIT_FAILURE);
    }

    //sets handleInterruption as callback for SIGINT signals
    signal(SIGINT, handleInterruption);
    signal(SIGTERM, handleInterruption);

    char* ipAddress = argv[1];
    unsigned int port = atoi(argv[2]);

    if (argc == 5) { //server is a backup server
        char* primaryIpAddress = argv[3];
        unsigned int primaryPort = atoi(argv[4]);
        Address primaryAddress;
        memset(&(primaryAddress), 0, sizeof(primaryAddress));
        primaryAddress.sin_family    = AF_INET; 
        primaryAddress.sin_addr.s_addr = inet_addr(primaryIpAddress); 
        primaryAddress.sin_port = htons(primaryPort); 
        server = new Server(ipAddress, port, primaryAddress);
    } else {
        server = new Server(ipAddress, port);
    }
    int seqNum = 0;
    

    while (RUNNING) {
        int64_t timestampMilliseconds = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        try {
            server->listen(seqNum, timestampMilliseconds);
            seqNum++;
        } catch (const std::runtime_error &exc) {
            if (RUNNING)
                std::cerr << exc.what();
        }
    }
    std::cout << "\nExiting..." << std::endl;
}
