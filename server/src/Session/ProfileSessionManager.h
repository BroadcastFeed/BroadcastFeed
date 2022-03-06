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
    map<string, Profile> users; //TODO start using database for users
    map<string, vector<Address>> sessions;

    bool profileExists(string username);
    Profile newProfile(string username);
    Profile getProfile(string username);

public:
    ProfileSessionManager();
    void login(pair<string, Address> sessionAttempt);
    explicit operator std::string() const;
};