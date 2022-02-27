#include "Notification.h"

Notification::Notification(int id, int timestamp, int length, int pendingReaders, std::string message){
    this.id = id;
    this.timestamp = timestamp;
    this.length = length;
    this.pendingReaders = pendingreaders;
    this.message = message;
}

Notification::getId(){
    return this.id;
}

Notification::getTimestamp(){
    return this.timestamp;
}

Notification::getLength(){
    return this.length;
}

Notification::getPendingReaders(){
    return this.pendingReaders;
}

Notification::getMessage(){
    return this.message;
}

Notification::decreasePendingReaders(){
    this.pendingReaders--;
}