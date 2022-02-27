#pragma once
#include <string>
#include <vector>
#include "Profile.h"

class State{
    private:
        std::vector<Profile> users;

    public:
        void addUser(std::string newUsername);
        std::vector<Profile> getUsers();
}