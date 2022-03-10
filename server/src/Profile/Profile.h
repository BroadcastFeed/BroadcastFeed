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
    vector<Profile> followers;
    vector<Notification> pendingNotifications;

public:
    Profile(string username);
    Profile();
    int getActiveSessions();
    string getName();
    vector<Profile> getFollowers();
    vector<Notification> getPendingNotifications();
    void addFollower(Profile newFollower);
    void addNotification(Notification newNotification);
    void startSession();
    void endSession();
    Notification removeNotification();
    operator std::string() const; 
};

