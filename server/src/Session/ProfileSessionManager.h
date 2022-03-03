#pragma once

#include <string>
#include <vector>
#include "../Database/Database.h"
#include "Profile.h"
#include "../Notification/Notification.h"

class ProfileSessionManager {
private:
    Database database;
    std::vector<Profile> activeUsers;

public:
    void addUser(std::string username);

    bool userIsActive(std::string username);

    void login(std::string username);
};