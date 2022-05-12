#pragma once

#include <vector>

#include "Communication/Packet.h"
#include "Communication/CommunicationManager.h"

using std::vector;

class BackupManager {
private:
    inline static bool isPrimary = false; 
    inline static Address primaryServerAddress = {};
    inline static vector<Address> serverAddresses = vector<Address>();

public:
    static void replicateToBackups(Packet packet);

    static void newBackupServer(Address serverAddress);
    static void removeBackupServer(Address serverAddress);

    static bool isPrimaryServer();
    static void setServerAsPrimary();
    static void setPrimaryServerAddress(Address address);
    static Address getPrimaryServerAddress();
};