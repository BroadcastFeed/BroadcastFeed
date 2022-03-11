#pragma once

#include <string>
#include <vector>
#include <map>
#include "../Profile/Profile.h"


class Database {
private:
    std::map<string, Profile> users;

public:
    Database();
    void save();
    bool userExists(const std::string& username);
    Profile& addUser(const std::string& newUsername);

    std::vector<Profile> getUsers() const;
    Profile getUser(const std::string& username);
    void updateUser(string username, Profile newProfile);
    void addNotification(const string& username, const Notification& notification);
    void addFollower(const string& followedUsername, const string& followerUsername);
    explicit operator std::string() const;
};
