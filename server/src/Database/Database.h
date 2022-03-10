#pragma once

#include <string>
#include <vector>
#include <map>
#include "../Profile/Profile.h"


class Database {
private:
    std::map<string, Profile> users;

public:
    bool userExists(const std::string& username);
    void addUser(const std::string& newUsername);
    std::vector<Profile> getUsers() const;
    Profile getUser(const std::string& username);
    void updateUser(string username, Profile newProfile);
    void addFollowers(string username, string follower);
    explicit operator std::string() const;
};
