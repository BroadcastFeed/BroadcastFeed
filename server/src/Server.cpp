#include "Server.h"

Server::Server(char* ipAddress, unsigned int port) : communicationManager(ipAddress, port) {}

Packet Server::listen(int seqn, int64_t timestamp){
    return this->communicationManager.listen(seqn, timestamp);
}

void Server::handlePacket(Packet packet){
    if (packet.getType() == 1){
        //START message
        this->profileSessionManager.login(packet.getMessage());
    }
    if (packet.getType() == 2){
        //FOLLOW message
    }
    else if (packet.getType() == 3){
        //SEND message
        int pendingReaders = 0; //change later
        Notification notification = Notification(packet.getSeqNum(), packet.getTimestamp(), packet.getLength(), pendingReaders, packet.getMessage());
        //this->notificationManager.sendNotification(notification);
    }
}

