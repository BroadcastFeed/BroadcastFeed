#include "Packet.h"

Packet::Packet(int type, int seqNum, int length, int timestamp, std::string message){
    this->type = type;
    this->seqNum = seqNum;
    this->length = length;
    this->timestamp = timestamp;
    this->message = message;
}

int Packet::getType(){
    return this->type;
}

int Packet::getSeqNum(){
    return this->seqNum;
}

int Packet::getLength(){
    return this->length;
}

int Packet::getTimestamp(){
    return this->timestamp;
}

std::string Packet::getMessage(){
    return this->message;
}

Packet::operator std::string() const { 
    std::string str;
    str += "Type: " + std::to_string(this->type) + "\n";
    str += "Seqn: " + std::to_string(this->seqNum) + "\n";
    str += "Length: " + std::to_string(this->length) + "\n";
    str += "Timestamp: " + std::to_string(this->timestamp) + "\n";
    str += "Message: " + this->message;
    return str; 
}