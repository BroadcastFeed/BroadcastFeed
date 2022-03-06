#include <arpa/inet.h>
#include "ProfileSessionManager.h"

ProfileSessionManager::ProfileSessionManager() : sessions() {}

void ProfileSessionManager::login(pair<string,Address> sessionAttempt) {
    string username = sessionAttempt.first;
    Address address = sessionAttempt.second;
    database.addUser(username);
    if(!sessions.contains(username)){
        std::vector<Address> newVector = {address};
        sessions[username] = newVector;
    }
    else if(sessions[username].size() < 2){
        this->sessions[username].push_back(address);
    }
}

//right now only printing ipv4
ProfileSessionManager::operator std::string() const { 
    std::string str;
    str += "Sessions: \n";
    for(auto const& x: this->sessions) {
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
