#pragma once
#include <string>
#include <vector>
#include "Database.h"
#include "Profile.h"
#include "Notification.h"

class ProfileSessionManager{
    private:
        Database database;
        std::vector<Profile> activeUsers;

    public:
        void addUser(std::string username);
        bool userIsActive(std::string username);
        void login(std::string username);
};