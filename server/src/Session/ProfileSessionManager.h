#pragma once

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <netinet/in.h>
#include "../Database/Database.h"
#include "../Profile/Profile.h"
#include "../Notification/Notification.h"

using std::vector;
using std::string;
using std::pair;
using std::map;

class ProfileSessionManager {
    typedef sockaddr_in Address;

private:

    Database database;
    map<string, vector<Address>> sessions;

public:
    ProfileSessionManager();
    void login(pair<string, Address> sessionAttempt);
    explicit operator std::string() const;
};