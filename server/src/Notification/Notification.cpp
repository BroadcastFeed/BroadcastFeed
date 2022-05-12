#include "Notification.h"

Notification::Notification(int id, int64_t timestamp, int length, string sender, string message) {
    this->id = id;
    this->timestamp = timestamp;
    this->length = length;
    this->sender = sender;
    this->message = message;
    this->lastReadBySession = 0;
}

string Notification::serialize() {
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

std::string Notification::getSender() {
    return this->sender;
}

void Notification::setSender(std::string sender) {
    this->sender = sender;
}

int Notification::getLastReadBySession() {
    return this->lastReadBySession;
}

void Notification::markAsRead(int sessionId) {
    this->lastReadBySession = sessionId;
}