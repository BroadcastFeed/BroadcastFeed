#include <arpa/inet.h>
#include "ProfileSessionManager.h"
#include "../Communication/CommunicationManager.h"

void ProfileSessionManager::registerNewSession(const string& user, Address address) {
    database.addUser(user);
    if(!userToSessionsMap.contains(user)){
        std::vector<Address> newVector = {Address()};
        userToSessionsMap.at(user) = newVector;
    }
    else if(userToSessionsMap[user].size() < 2){
        userToSessionsMap.at(user).push_back(address);
    }
}

void ProfileSessionManager::addNotification(const string& username, const Notification& notification){
    ProfileSessionManager::database.addNotification(username, notification);
}

void ProfileSessionManager::addFollower(const string& followed, const string& follower){
    ProfileSessionManager::database.addFollower(followed, follower);
}

//right now only printing ipv4
/* TODO UPDATE
ProfileSessionManager::operator std::string() const { 
    std::string str;
    str += "Sessions: \n";
    for(auto const& x: this->userToSessionsMap) {
        str += "    Profile: " + x.first + "\n    Addresses:";
        for(const Address& a : x.second){
            char stringAddr[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(a.sin_addr), stringAddr, INET_ADDRSTRLEN);
            str += " " + (string) stringAddr + ":";
            str += std::to_string(a.sin_port);
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
    auto addresses = userToSessionsMap.at(username);
    for (Address session : addresses) {
        if (session == address)
            return true;
    }
    return false;
}

vector<Address> ProfileSessionManager::getOpenedSessions(const string &username) {
    return userToSessionsMap.at(username);
}
*/