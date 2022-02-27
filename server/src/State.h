#pragma once
#include <string>
#include <vector>
#include "Profile.h"

class State{
    private:
        std::vector<Profile> users;

    public:
        void addUser(Profile user);
        std::vector<Profile> getUsers();
}