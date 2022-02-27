#pragma once
#include <vector>
#include <string>
#include "Notification.h"

class Profile {

    private:

        std::string username;
        std::vector<Profile> followers;
        std::vector<Notification> notifications;

    public:

        Profile(std::string username);
        std::string getName();
        std::vector<Profile> getFollowers();
        std::vector<Notification> getNotifications();
        void addFollower(Profile newFollower);
        void addNotification(Notification newNotification);
        Notification removeNotification();
}

