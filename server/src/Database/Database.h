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
    void addFollower(const string& followedUsername, const string& followerUsername);
    explicit operator std::string() const;
};
