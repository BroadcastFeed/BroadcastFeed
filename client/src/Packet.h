#pragma once 
#include <string>

class Packet{
    private:
        int type;
        int seqNum;
        int length;
        int timestamp;
        std::string message;

    public:
        Packet(int type, int seqNum, int length, int timestamp, std::string message);
        Packet(std::string serializedPacket);
        int getType();
        int getSeqNum();
        int getLength();
        int getTimestamp();
        std::string getMessage();
        std::string serialize();
        operator std::string() const; 
};