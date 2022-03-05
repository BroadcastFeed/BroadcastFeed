#include "Notification.h"

Notification::Notification(int id, int64_t timestamp, int length, int pendingReaders, std::string message) {
    this->id = id;
    this->timestamp = timestamp;
    this->length = length;
    this->pendingReaders = pendingReaders;
    this->message = message;
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