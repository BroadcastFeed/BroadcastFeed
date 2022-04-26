#include "Packet.h"

#include <sstream>

Packet::Packet(PacketType type, int seqNum, int length, int64_t timestamp, std::string message, std::string username){
    this->type = type;
    this->seqNum = seqNum;
    this->length = length;
    this->timestamp = timestamp;
    this->username = username;
    this->message = message;
}


Packet::Packet(PacketType type, std::string message, std::string username){
    this->type = type;
    this->seqNum = -1;
    this->length = message.length();
    this->timestamp = -1;
    this->username = username;
    this->message = message;
}

Packet::Packet(std::string serializedPacket){
    parseFromString(serializedPacket);
}

void Packet::parseFromString(const std::string &serializedPacket) {
    std::stringstream ss(serializedPacket);
    std::string section;

    std::getline(ss, section, ',');
    type = static_cast<PacketType>(stoi(section));

    std::getline(ss, section, ',');
    seqNum = stoi(section);

    std::getline(ss, section, ',');
    length = stoi(section);

    std::getline(ss, section, ',');
    timestamp = atoll(section.c_str());

    std::getline(ss, section, ',');
    username = section;

    std::getline(ss, section);
    message = section;
}


void Packet::setTimestamp(int64_t timestamp){
    this->timestamp = timestamp;
}

void Packet::setSeqNum(int seqNum){
    this->seqNum = seqNum;
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

int64_t Packet::getTimestamp(){
    return this->timestamp;
}

std::string Packet::getMessage(){
    return this->message;
}

std::string Packet::getUsername(){
    return this->username;
}

std::string Packet::serialize(){
    std::string str;
    str += std::to_string(this->type) + ",";
    str += std::to_string(this->seqNum) + ",";
    str += std::to_string(this->length) + ",";
    str += std::to_string(this->timestamp) + ",";
    str += this->username + ",";
    str += this->message;
    return str; 
}

Packet::operator std::string() const { 
    std::string str;
    str += "Type: " + std::to_string(this->type) + "\n";
    str += "Seqn: " + std::to_string(this->seqNum) + "\n";
    str += "Length: " + std::to_string(this->length) + "\n";
    str += "Timestamp: " + std::to_string(this->timestamp) + "\n";
    str += "Username: " + this->username + "\n";
    str += "Message: " + this->message + "\n";
    return str; 
}