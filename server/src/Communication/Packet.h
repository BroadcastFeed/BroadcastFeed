#pragma once 
#include <string>

enum PacketType { CONNECT, SEND, FOLLOW, DISCONNECT };

class Packet{
    private:
        PacketType type;
        int seqNum;
        int length;
        int64_t timestamp;
        std::string message;

    public:
        Packet(PacketType type, int seqNum, int length, int64_t timestamp, std::string message);
        Packet(PacketType type, std::string message);
        Packet(std::string serializedPacket);
        void setTimestamp(int64_t timestamp);
        void setSeqNum(int seqNum);
        int getType();
        int getSeqNum();
        int getLength();
        int64_t getTimestamp();
        std::string getMessage();
        std::string serialize();
        operator std::string() const; 
};