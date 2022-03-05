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
    vector<Profile> activeUsers;

public:
    void addActiveUser(string username);

    bool userIsActive(string username);

    void login(string username);
};