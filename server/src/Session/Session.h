#pragma once

#include<thread>
#include "../Communication/CommunicationManager.h"
#include "../Profile/Profile.h"

using std::thread;

class Session {

private:
    Address address;
    Profile associatedUser;
    thread connectionThread;
public:
    Session(const Address &address, const Profile &associatedUser);
    Address getAddress();
    Profile getAssociatedUser();
    thread getConnectionThread();

};
