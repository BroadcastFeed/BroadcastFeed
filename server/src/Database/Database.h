#pragma once

#include <string>
#include <vector>
#include <map>
#include "../Profile/Profile.h"


class Database {
private:
    std::map<string, Profile> users;

public:
    Database();  //constructor loads data from file if possible
    ~Database(); //deconstruct saves data and deletes pointers
    void save();

    bool userExists(const std::string &username);

    void addUser(const std::string &newUsername);

    Profile *getUser(const std::string &username);

    std::vector<Profile> getUsers() const;

    bool addNotification(const string &username, const Notification &notification);
    void popNotification(const string &username);

    bool addFollower(const string &followedUsername, const string &followerUsername);

    bool userIsFollowed(Profile *followed, Profile *follower);

    explicit operator std::string() const;
};
