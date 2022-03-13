#pragma once

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <thread>
#include <netinet/in.h>
#include "../Database/Database.h"
#include "../Profile/Profile.h"
#include "../Notification/Notification.h"
#include "../Session/Session.h"

using std::vector;
using std::string;
using std::pair;
using std::map;
using std::thread;

class ProfileSessionManager {
    typedef sockaddr_in Address;

private:
    inline static Database database = Database();
    inline static map<string, vector<Session>> userToSessionsMap = {};
    inline static vector<thread> threadList = {};

public:
    static void registerNewSession(const string& user, Address sessionAddress, Address serverAddress, unsigned int socketDescriptor);
    static void addNotification(const string& username, const Notification& notification);
    static void addFollower(const string& followed, const string& follower);
    static bool validateProfileSession(const string& username, const Address& address);
    static vector<Address> getOpenedSessions(const string& username);
    explicit operator std::string() const;
};