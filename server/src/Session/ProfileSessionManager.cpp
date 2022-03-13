#include <arpa/inet.h>
#include "ProfileSessionManager.h"
#include "../Communication/CommunicationManager.h"

void ProfileSessionManager::registerNewSession(
        const string& user, 
        Address sessionAddress, 
        Address serverAddress,
        unsigned int socketDescriptor
        ) {
    database.addUser(user);
    Profile* profile = database.getUser(user);
    Session* session = new Session(profile, sessionAddress, serverAddress, socketDescriptor);
    if(!userToSessionsMap.contains(user)){
        userToSessionsMap[user] = {session};
    }
    else if(userToSessionsMap[user].size() < 2){
        userToSessionsMap.at(user).push_back(session);
    }
}

void ProfileSessionManager::removeSession(const string& user, Address sessionAddress){
    auto sessions = userToSessionsMap.at(user);
    for (int i = 0; i < sessions.size(); i++) {
        auto session = sessions[i];
        sessions.erase(sessions.begin() + i);
        delete(session);
    }
}

void ProfileSessionManager::addNotification(const string& username, const Notification& notification){
    ProfileSessionManager::database.addNotification(username, notification);
}

void ProfileSessionManager::addFollower(const string& followed, const string& follower){
    ProfileSessionManager::database.addFollower(followed, follower);
}

ProfileSessionManager::operator std::string() const { 
    std::string str;
    str += "Sessions: \n";
    for(auto const& x: this->userToSessionsMap) {
        str += "    Profile: " + x.first + "\n    Addresses:";
        for(Session* s : x.second){
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

constexpr bool operator==(const Address& lhs, const Address& rhs) {
    return lhs.sin_port == rhs.sin_port && lhs.sin_addr.s_addr == rhs.sin_addr.s_addr
           && lhs.sin_family == rhs.sin_family;
}

bool ProfileSessionManager::validateProfileSession(const string &username, const Address& address) {
    auto sessions = userToSessionsMap.at(username);
    for (Session* s : sessions) {
        if (s->getAddress() == address)
            return true;
    }
    return false;
}

vector<Session*> ProfileSessionManager::getOpenedSessions(const string &username) {
    return userToSessionsMap.at(username);
}

ProfileSessionManager::~ProfileSessionManager() {
    for(auto const& x : this->userToSessionsMap) {
        for(Session* s : x.second){
            delete(s);
        }    
    }
}