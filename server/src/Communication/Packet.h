#pragma once

#include <string>
#include <sstream>

#include "../Notification/Notification.h"

enum PacketType {
    ACKNOWLEDGE, CONNECT, SEND, FOLLOW, DISCONNECT, NOTIFICATION, SERVER_SWITCH, //client-server and server-server packets
    CONNECT_BACKUP, PING, PONG,  //server-server packets
};
    
const std::string PACKET_TYPE_NAMES[] = {
    "ACKNOWLEDGE", "CONNECT", "SEND", "FOLLOW", "DISCONNECT", "NOTIFICATION", "SWITCH MAIN SERVER", 
    "CONNECT BACKUP SERVER"
};

class Packet {
private:
    PacketType type;
    int seqNum;
    int length;
    int64_t timestamp;
    std::string username;
    std::string message;

public:
    Packet(PacketType type, int seqNum, int length, int64_t timestamp, std::string message, std::string username);

    Packet(PacketType type, std::string message, std::string username);

    Packet(std::string serializedPacket);
    
    Packet(Notification notification);

    void setTimestamp(int64_t timestamp);

    void setSeqNum(int seqNum);

    void setUsername(std::string username);

    int getType();

    int getSeqNum();

    int getLength();

    int64_t getTimestamp();

    std::string getMessage();

    void parseFromString(const std::string &serializedPacket);

    std::string serialize();

    std::string getUsername();
    
    operator std::string() const;
};