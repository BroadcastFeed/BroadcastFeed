#include "Notification.h"

Notification::Notification(int id, int64_t timestamp, int length, string sender, string message) {
    this->id = id;
    this->timestamp = timestamp;
    this->length = length;
    this->sender = sender;
    this->message = message;
}

string Notification::serialize(){
    return sender + ":" + message;
}

int Notification::getId() {
    return this->id;
}

int64_t Notification::getTimestamp() {
    return this->timestamp;
}

int Notification::getLength() {
    return this->length;
}

std::string Notification::getMessage() {
    return this->message;
}

std::vector<int> Notification::getReadBySessions(){
    return this->readBySessions;
}

void Notification::markAsRead(int sessionId) {
    this->readBySessions.push_back(sessionId);
}