#pragma once

#include <vector>
#include <string>

using std::string;

class Notification {
private:
    int id;
    int64_t timestamp;
    int length;
    int lastReadBySession;
    string sender;
    string message;

public:
    Notification(int id, int64_t timestamp, int length, string sender, string message);

    string serialize();

    int getId();

    int64_t getTimestamp();

    int getLength();

    string getMessage();
    
    string getSender();

    int getLastReadBySession();

    void markAsRead(int sessionId);

};