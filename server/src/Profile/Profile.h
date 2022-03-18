#pragma once

#include <vector>
#include <queue>
#include <string>
#include <mutex>
#include "../Notification/Notification.h"

using std::string;
using std::vector;
using std::queue;
using std::mutex;

class Profile {

private:
    int activeSessions;
    string username;
    vector<Profile*> followers;
    vector<Notification> producerBuffer;
    vector<Notification> pendingNotifications;

    mutex *notificationsQueueMutex;

public:
    explicit Profile(string username);
    Profile();

    int getActiveSessions();
    string getName();
    vector<Profile*> getFollowers();
    vector<Notification> getNotificationsToBeSent();
    Notification getTopNotification();

    void addFollower(Profile* newFollower);

    void addNotificationToBeSent(Notification notification);
    void addNotificationToBeRead(Notification notification);
    void markTopAsRead(int sessionId);

    bool hasNotificationToBeSent();
    bool hasNotificationToBeRead();

    Notification popNotificationToBeSent();
    Notification popNotificationToBeRead();

    operator std::string() const; 
};

