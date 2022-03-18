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

void handleInterruption(int signal){
    RUNNING = false;
    server->halt();
}

//the syntax is ./server <IP ADDRESS> <PORT>
int main(int argc, char **argv) {
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }

    //sets handleInterruption as callback for SIGINT signals
    signal(SIGINT, handleInterruption);
    signal(SIGTERM, handleInterruption);

    char *ipAddress = argv[1];
    unsigned int port = atoi(argv[2]);
    server = new Server(ipAddress, port);
    int seqNum = 0;
    
    std::cout << "Server running, press Ctrl-C to save and exit." << std::endl;
    while (RUNNING) {
        int64_t timestampMilliseconds = duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
        try{
            server->listen(seqNum, timestampMilliseconds);
            seqNum++;
        } catch (const std::runtime_error &exc){
            if(RUNNING)
                std::cerr << exc.what();
        }
    }
    std::cout << "\nExiting..." << std::endl; 
}
