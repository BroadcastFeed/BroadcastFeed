#include "Notification.h"

Notification::Notification(int id, int64_t timestamp, int length, int pendingReaders, string sender, string message) {
    this->id = id;
    this->timestamp = timestamp;
    this->length = length;
    this->pendingReaders = pendingReaders;
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

int Notification::getPendingReaders() {
    return this->pendingReaders;
}

std::string Notification::getMessage() {
    return this->message;
}

void Notification::decreasePendingReaders() {
    this->pendingReaders--;
}