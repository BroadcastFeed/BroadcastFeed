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
    void addUser(string newUsername);
    vector<Profile> getUsers();
    operator std::string() const; 
};
