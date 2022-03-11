#pragma once

#include <string>

using std::string;

class Notification {
private:
    int id;
    int64_t timestamp;
    int length;
    int pendingReaders;
    string sender;
    string message;

public:
    Notification(int id, int64_t timestamp, int length, int pendingReaders, string sender, string message);

    int getId();
    int64_t getTimestamp();
    int getLength();
    int getPendingReaders();
    string getMessage();
    void decreasePendingReaders();
    string serialize();

};