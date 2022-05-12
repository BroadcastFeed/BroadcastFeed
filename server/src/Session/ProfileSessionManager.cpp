#include <arpa/inet.h>
#include <iostream>
#include "ProfileSessionManager.h"

bool ProfileSessionManager::registerNewSession(
        const string &user,
        Address sessionAddress,
        Address serverAddress,
        unsigned int socketDescriptor
) {
    database.addUser(user);
    Profile *profile = database.getUser(user);
    if (profile != nullptr) {
        if (!userToSessionsMap.contains(user)) {
            Session *session = new Session(profile, sessionAddress, socketDescriptor, 0);
            session->initSession();
            session->setAsOnlySession();
            userToSessionsMap[user] = {session};
            return true;
        } else if (userToSessionsMap[user].size() < 2) {
            Session *session = new Session(profile, sessionAddress, socketDescriptor,
                                           !userToSessionsMap[user][0]->getSessionNum());
            userToSessionsMap[user][0]->unsetAsOnlySession();
            userToSessionsMap[user].push_back(session);
            session->initSession();
            return true;
        }
    }
    return false;
}

bool ProfileSessionManager::addNotification(const string &username, const Notification &notification) {
    return ProfileSessionManager::database.addNotification(username, notification);
}

bool ProfileSessionManager::addFollower(const string &followed, const string &follower) {
    return ProfileSessionManager::database.addFollower(followed, follower);
}

ProfileSessionManager::operator std::string() const {
    std::string str;
    str += "Sessions: \n";
    for (auto const &x: this->userToSessionsMap) {
        str += "    Profile: " + x.first + "\n    Addresses:";
        for (Session *s: x.second) {
            char stringAddr[INET_ADDRSTRLEN];
            Address address = s->getAddress();
            inet_ntop(AF_INET, &address.sin_addr, stringAddr, INET_ADDRSTRLEN);
            str += " " + (string) stringAddr + ":";
            str += std::to_string(s->getAddress().sin_port);
        }
        str += "\n\n";
    }
    return str;
}

bool ProfileSessionManager::removeSession(const string &user, Address sessionAddress) {
    if (userToSessionsMap.contains(user)) {
        auto sessions = &userToSessionsMap.at(user);
        for (int i = 0; i < sessions->size(); i++) {
            auto session = sessions->at(i);
            if (session->getAddress() == sessionAddress) {
                session->closeSession();
                sessions->erase(userToSessionsMap[user].begin() + i);
                if (sessions->empty()) {
                    userToSessionsMap.erase(user);
                } else {
                    userToSessionsMap[user][0]->setAsOnlySession();
                }
            }
        }

        return true;
    }
    return false;
}

bool ProfileSessionManager::validateProfileSession(const string &username, const Address &address) {
    auto sessions = userToSessionsMap.at(username);
    for (Session *s: sessions) {
        if (s->getAddress() == address)
            return true;
    }
    return false;
}

bool ProfileSessionManager::userCanConnect(string username) {
    if(userToSessionsMap.contains(username)){
        return userToSessionsMap.at(username).size() < 2;
    } else return true;
}

vector<Session *> ProfileSessionManager::getOpenedSessions(const string &username) {
    return (hasOpenedSessions(username)) ? userToSessionsMap.at(username) : vector<Session *>();
}

bool ProfileSessionManager::hasOpenedSessions(const string &username) {
    return userToSessionsMap.contains(username) && !userToSessionsMap.at(username).empty();
}

ProfileSessionManager::~ProfileSessionManager() {
    for (auto const &x: this->userToSessionsMap) {
        for (Session *s: x.second) {
            delete (s);
        }
    }
}

std::string ProfileSessionManager::getSessionsString() {
    std::string str;
    str += "Sessions: \n";
    for (auto const &x: userToSessionsMap) {
        str += "    Profile: " + x.first + "\n    Addresses:";
        for (Session *s: x.second) {
            char stringAddr[INET_ADDRSTRLEN];
            Address address = s->getAddress();
            inet_ntop(AF_INET, &address.sin_addr, stringAddr, INET_ADDRSTRLEN);
            str += " " + (string) stringAddr + ":";
            str += std::to_string(htons(s->getAddress().sin_port));
        }
        str += "\n\n";
    }
    return str;
}
