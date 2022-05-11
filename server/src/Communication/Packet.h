#pragma once

#include <string>

#include "../Notification/Notification.h"

enum PacketType {
    ACKNOWLEDGE, CONNECT, SEND, FOLLOW, DISCONNECT, PING, PONG, ELECTION, ELECTED
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