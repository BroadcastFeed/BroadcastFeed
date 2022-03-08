#pragma once

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <netinet/in.h>
#include "../Database/Database.h"
#include "../Profile/Profile.h"
#include "../Notification/Notification.h"

using std::vector;
using std::string;
using std::pair;
using std::map;

class ProfileSessionManager {
    typedef sockaddr_in Address;

private:
    Database database;
    map<string, vector<Address>> userToSessionsMap;

    /*
    ernestito:
        lidar com notificações:
            map<string, Address>
        ok, faz senso, podendo criar thread na hora

        decodificar remetente:
            map<Address, string>
        problema: quem cria/chama as threads? ficam em busywait?
        criar threads na hora? 

        problemas ultrapassam dilema "passar username na mensagem"

    

    riquito:
        map<string, pair<Address, thread>>
        map<Address, pair<string, thread>>
    */

public:
    ProfileSessionManager();
    Address login(string user, Address address);
    explicit operator std::string() const;
};