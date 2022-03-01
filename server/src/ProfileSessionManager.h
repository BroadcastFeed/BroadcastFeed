#pragma once
#include <string>
#include "Database.h"
#include "Profile.h"
#include "Notification.h"

class ProfileSessionManager{
    private:
        Database database;

    public:
        bool consultUsername(std::string username); //returns the existance or not of a give username
        void addNewUser(std::string username);
        void login(std::string username);
};