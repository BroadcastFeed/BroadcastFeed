//
// Created by wmespindula on 11/05/22.
//

#pragma once

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

typedef sockaddr_in Address;

inline std::ostream& operator<<(std::ostream& os, const Address &address) {
    char stringAddr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &address.sin_addr, stringAddr, INET_ADDRSTRLEN);
    os << std::string(stringAddr) + ":" << std::to_string(htons(address.sin_port));
    return os;
}

inline std::string addressToString(const Address &address) {
    char stringAddr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &address.sin_addr, stringAddr, INET_ADDRSTRLEN);
    return std::string(stringAddr) + ":" + std::to_string(htons(address.sin_port));
}

constexpr bool operator==(const Address &lhs, const Address &rhs) {
    return lhs.sin_port == rhs.sin_port && lhs.sin_addr.s_addr == rhs.sin_addr.s_addr
           && lhs.sin_family == rhs.sin_family;
}