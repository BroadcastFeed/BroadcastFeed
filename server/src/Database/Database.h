#pragma once

#include <string>
#include <vector>
#include "../Profile/Profile.h"


class Database {
private:
    std::vector<Profile> users;

public:
    bool userExists(const std::string username);
    void addUser(const std::string& newUsername);
    std::vector<Profile> getUsers();
    Profile getUser(const std::string& username);
    explicit operator std::string() const;
};
