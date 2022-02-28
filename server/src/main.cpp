#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <errno.h>
#include "CommunicationManager.h"

#define MAXSIZE 1024

//for now, the syntax is ./server <IP ADDRESS> <PORT>

int main(int argc, char** argv) { 
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }
    char* ipAddress = argv[1];
    unsigned int port = atoi(argv[2]);
    
    CommunicationManager communicationManager = CommunicationManager(ipAddress, port);
    communicationManager.runServer();
}
