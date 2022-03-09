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
    map<string, vector<Address>> userToSessionsMap;

public:
    ProfileSessionManager();
    void registerNewSession(const string& user, Address address);
    bool validateProfileSession(const string& username, const Address& address);
    vector<Address> getOpenedSessions(const string& username);
    explicit operator std::string() const;
};