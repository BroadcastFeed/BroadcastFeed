#include "Session.h"

Session::Session(const Address &address, const Profile &associatedUser) : address(
        address), associatedUser(associatedUser) {
    connectionThread = std::thread();
}

Session::getAddress(){
    return this->address;
}

Session:getAssociatedUser(){
    return this->associatedUser;
}

Session:getConnectionThread(){
    return this->connectionThread;
}

Profile Session::getAssociatedUser() {
    return this->getAssociatedUser();
}
