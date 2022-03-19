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
    vector<Notification> getProducerBuffer();
    Notification getTopPendingNotification();

    void addFollower(Profile* newFollower);

    void addNotificationToProducerBuffer(const Notification& notification);
    void addPendingNotification(const Notification& notification);
    void markTopAsRead();

    bool hasNotificationInBuffer();
    bool hasPendingNotification();

    Notification popNotificationFromBuffer();
    Notification popPendingNotification();

    operator std::string() const;
};

