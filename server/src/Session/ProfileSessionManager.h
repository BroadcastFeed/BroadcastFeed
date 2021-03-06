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
#include "../Communication/Address.h"

using std::vector;
using std::string;
using std::pair;
using std::map;
using std::thread;

class ProfileSessionManager {
private:
    inline static Database database = Database();
    inline static map<string, vector<Session *>> userToSessionsMap = {};

public:
    static bool registerNewSession(const string &user, Address sessionAddress, Address serverAddress,
                                   unsigned int socketDescriptor, bool shouldBeActive);
    static bool removeSession(const string &user, Address sessionsAddress);
    static bool validateProfileSession(const string &username, const Address &address);
    static vector<Session *> getOpenedSessions(const string &username);
    static bool hasOpenedSessions(const string &username);
    static std::string getSessionsString();
    static std::string getProfilesString();

    static bool addNotification(const string &username, const Notification &notification);
    static void popNotification(const string &username);
    static bool addFollower(const string &followed, const string &follower);

    static bool userCanConnect(string username);

    ~ProfileSessionManager();
};