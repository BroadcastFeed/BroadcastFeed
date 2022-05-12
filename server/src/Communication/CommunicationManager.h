#pragma once

#include <string>
#include "Packet.h"
#include "../Notification/Notification.h"
#include "Address.h"
#include <netinet/in.h>
#include <utility>
#include <thread>
#include <chrono>
#include <arpa/inet.h>

using std::string;

class CommunicationManager {
private:
    unsigned int socketDescriptor;
    Address serverAddress;
    
    void sendPacket(Packet packet, Address destinationAddress);

    std::thread *waitingPongThread;
    bool isPingRunning = false;
    Address pingedAddress;
    bool waitingPong = false;

    void sendPing(Address testedServerAddress);
    void waitForPong(int timeout);

public:
    CommunicationManager(char *ipAddress, unsigned int port);

    std::pair<Packet, Address> listen(int seqn, int64_t timestamp);
    static Address createDestinationAddress(char *ipAddress, unsigned int port);
    void sendAcknowledge(Address clientAddress);
    bool isReachable(Address testedServerAddress, int timeout = 10000);
    void sendPong(Address testedServerAddress);
    void receivePong(Address testedServerAddress);
    void sendServerSwitchToClient(Address clientAddress);
    void connectAsBackupServer(Address primaryServer);

    unsigned int getDescriptor();
    Address getAddress();


};