#pragma once

#include <vector>
#include <queue>
#include <string>
#include "../Notification/Notification.h"

using std::string;
using std::vector;
using std::queue;

class Profile {

private:
    int activeSessions;
    string username;
    vector<Profile&> followers;
    vector<Notification> notificationsToBeSent;
    vector<Notification> notificationsToBeRead;

public:
    Profile(string username);
    Profile();
    int getActiveSessions();
    string getName();
    vector<Profile&> getFollowers();

    vector<Notification> getNotificationsToBeSent();

    void addFollower(Profile& newFollower);


    void startSession();
    void endSession();

    void addNotificationToBeSent(Notification notification);
    void addNotificationToBeRead(Notification notification);

    bool hasNotificationToBeSent();
    bool hasNotificationToBeRead();

    Notification popNotificationToBeSent();
    Notification popNotificationToBeRead();

    operator std::string() const; 
};

