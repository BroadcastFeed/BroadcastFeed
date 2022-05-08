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
    inline static map<string, vector<Session *>> userToSessionsMap = {};

public:
    static bool registerNewSession(const string &user, Address sessionAddress, Address serverAddress,
                                   unsigned int socketDescriptor);

    static bool removeSession(const string &user, Address sessionsAddress);

    static bool addNotification(const string &username, const Notification &notification);

    static bool addFollower(const string &followed, const string &follower);

    static bool validateProfileSession(const string &username, const Address &address);

    static bool userCanConnect(string username);

    static vector<Session *> getOpenedSessions(const string &username);

    static bool hasOpenedSessions(const string &username);

    explicit operator std::string() const;

    ~ProfileSessionManager();
};