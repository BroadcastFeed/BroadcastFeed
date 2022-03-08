#include <arpa/inet.h>
#include <thread>
#include "ProfileSessionManager.h"
#include "../Communication/CommunicationManager.h"

ProfileSessionManager::ProfileSessionManager() : userToSessionsMap() {}

Address ProfileSessionManager::login(string user, Address address) {
    database.addUser(user);
    if(!userToSessionsMap.contains(user)){
        std::vector<Address> newVector = {Address()};
        userToSessionsMap.at(user) = newVector;
    }
    else if(userToSessionsMap[user].size() < 2){
        this->userToSessionsMap.at(user).push_back(address);
    }
}

//right now only printing ipv4
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
