#pragma once

#include <string>

using std::string;

class Notification {
private:
    int id;
    int timestamp;
    int length;
    int pendingReaders;
    string message;

public:
    Notification(int id, int timestamp, int length, int pendingReaders, string message);

    int getId();

    int getTimestamp();

    int getLength();

    int getPendingReaders();

    string getMessage();

    void decreasePendingReaders();

};