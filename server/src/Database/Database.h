#pragma once

#include <string>
#include <vector>
#include "../Profile/Profile.h"

using std::string;
using std::vector;

class Database {
private:
    vector<Profile> users;

public:
    void addUser(const string& newUsername);
    vector<Profile> getUsers();
    Profile getUser(const string& username);
    explicit operator std::string() const;
};
