#pragma once

#include <vector>
#include <string>
#include "../Notification/Notification.h"

using std::string;
using std::vector;

class Profile {

private:
    int activeSessions;
    string username;
    vector<Profile> followers;
    vector<Notification> notifications;

public:
    Profile(string username);

    int getActiveSessions();

    string getName();

    vector<Profile> getFollowers();

    vector<Notification> getNotifications();

    void addFollower(Profile newFollower);

    void addNotification(Notification newNotification);

    void startSession();

    void endSession();

    Notification removeNotification();
};

