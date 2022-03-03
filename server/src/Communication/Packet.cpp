#include "Packet.h"

#include <sstream>

using std::string;
using std::stringstream;
using std::to_string;

Packet::Packet(int type, int seqNum, int length, int timestamp, string message) {
    this->type = type;
    this->seqNum = seqNum;
    this->length = length;
    this->timestamp = timestamp;
    this->message = message;
}

Packet::Packet(string serializedPacket) {
    stringstream ss(serializedPacket);
    string section;

    getline(ss, section, ',');
    this->type = stoi(section);

    getline(ss, section, ',');
    this->seqNum = stoi(section);

    getline(ss, section, ',');
    this->length = stoi(section);

    getline(ss, section, ',');
    this->timestamp = stoi(section);

    getline(ss, section, ',');
    this->message = section;
}

int Packet::getType() {
    return this->type;
}

int Packet::getSeqNum() {
    return this->seqNum;
}

int Packet::getLength() {
    return this->length;
}

int Packet::getTimestamp() {
    return this->timestamp;
}

string Packet::getMessage() {
    return this->message;
}

string Packet::serialize() {
    string str;
    str += to_string(this->type) + ",";
    str += to_string(this->seqNum) + ",";
    str += to_string(this->length) + ",";
    str += to_string(this->timestamp) + ",";
    str += this->message;
    return str;
}

Packet::operator string() const {
    string str;
    str += "Type: " + to_string(this->type) + "\n";
    str += "Seqn: " + to_string(this->seqNum) + "\n";
    str += "Length: " + to_string(this->length) + "\n";
    str += "Timestamp: " + to_string(this->timestamp) + "\n";
    str += "Message: " + this->message + "\n";
    return str;
}
