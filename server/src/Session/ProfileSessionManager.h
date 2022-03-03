#pragma once

#include <string>
#include <vector>
#include "../Database/Database.h"
#include "../Profile/Profile.h"
#include "../Notification/Notification.h"

using std::vector;
using std::string;

class ProfileSessionManager {
private:
    Database database;
    vector<Profile> activeUsers;

public:
    void addUser(string username);

    bool userIsActive(string username);

    void login(string username);
};