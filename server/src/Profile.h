#pragma once
#include <vector>
#include <string>

class Profile {

    private:

        std::string username;
        std::vector<Profile> followers;

    public:

        std::string getName();
        void addFollower(Profile newFollower);
}

