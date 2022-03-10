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
    inline static Database database = Database();
    inline static map<string, vector<Address>> userToSessionsMap = {};

public:
    static void registerNewSession(const string& user, Address address);
    static bool validateProfileSession(const string& username, const Address& address);
    static vector<Address> getOpenedSessions(const string& username);
    explicit operator std::string() const;
};