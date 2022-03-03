#pragma once

#include <string>

using std::string;

class Packet {
private:
    unsigned short type;
    int seqNum;
    int length;
    int timestamp;
    string message;

public:
    Packet(int type, int seqNum, int length, int timestamp, string message);

    Packet(string serializedPacket);

    int getType();

    int getSeqNum();

    int getLength();

    int getTimestamp();

    string getMessage();

    string serialize();

    operator string() const;
};