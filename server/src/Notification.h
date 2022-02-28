#pragma once
#include <string>

class Notification{
    private:
        int id;
        int timestamp;
        int length;
        int pendingReaders;
        std::string message;

    public:
        Notification(int id, int timestamp, int length, int pendingReaders, std::string message);
        int getId();
        int getTimestamp();
        int getLength();
        int getPendingReaders();
        std::string getMessage();
        void decreasePendingReaders();

};