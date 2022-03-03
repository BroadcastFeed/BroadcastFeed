#pragma once

#include <string>
#include <vector>
#include "../Session/Profile.h"

using std::string;
using std::vector;

class Database {
private:
    vector<Profile> users;

public:
    void addUser(string newUsername);

    vector<Profile> getUsers();
};