#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include <iostream>

#define PORT     8080
#define MAXSIZE 1024

//for now the syntax is ./client <IP ADDRESS>

int main(int argc, char** argv) { 
    if (argc != 2) {
        exit(EXIT_FAILURE);
    }
    char* ipAddress = argv[1]; 
    

    int socketDescriptor; // unique name identificator for socket
    //instanciate UDP socket
    if ((socketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) {
        perror("Socket creation failed!");
        exit(EXIT_FAILURE);
    }
     
    struct sockaddr_in serverAddress; //instanciate socket address struct

    memset(&serverAddress, 0, sizeof(serverAddress)); 
    // filling server information
    serverAddress.sin_family = AF_INET; //ipv4 family
    serverAddress.sin_port = htons(PORT); //converts port value to proper format
    serverAddress.sin_addr.s_addr = inet_addr(ipAddress); //converts ip to proper format
    unsigned int serverStructLength = sizeof(serverAddress);

    char buffer[MAXSIZE];
    std::string message = "Hello from client";

    if (sendto(socketDescriptor, message.data(), message.length(),
        MSG_CONFIRM, (struct sockaddr*) &serverAddress,
        sizeof(serverAddress)) < 0)
        std::cout << "Erro!";
    std::cout << "Message sent!" << std::endl;

    recvfrom(socketDescriptor, buffer, MAXSIZE,
        MSG_WAITALL, (struct sockaddr*) &serverAddress,
        &serverStructLength);
    std::cout << "Server: " << buffer << std::endl;

    close(socketDescriptor);
    return 0;
}
