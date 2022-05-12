#pragma once

#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <arpa/inet.h>

#include "Packet.h"
#include "../Notification/Notification.h"
#include "Address.h"

using std::string;

class CommunicationManager {
private:
    
    std::thread *waitingPongThread;
    bool isPingRunning = false;
    Address pingedAddress;
    bool waitingPong = false;

    void sendPing(Address testedServerAddress);
    void waitForPong(int timeout);

public:
    inline static unsigned int socketDescriptor = 0;
    inline static Address serverAddress = {};

    CommunicationManager(char *ipAddress, unsigned int port);

    std::pair<Packet, Address> listen(int seqn, int64_t timestamp);
    static Address createDestinationAddress(char *ipAddress, unsigned int port);
    void sendAcknowledge(Address clientAddress);
    bool isReachable(Address testedServerAddress, int timeout = 10000);
    void sendPong(Address testedServerAddress);
    void receivePong(Address testedServerAddress);
    static void sendPacket(Packet packet, Address destinationAddress);
    void sendServerSwitchToClient(Address clientAddress);
    void connectAsBackupServer(Address primaryServer);

    unsigned int getDescriptor();
    Address getAddress();


};