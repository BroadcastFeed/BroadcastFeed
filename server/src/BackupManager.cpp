#include "BackupManager.h"

void BackupManager::replicateToBackups(Packet packet) {
    for(Address address : serverAddresses) {
        CommunicationManager::sendPacket(packet, address);
    }
}

void BackupManager::newBackupServer(Address serverAddress) {
    BackupManager::serverAddresses.push_back(serverAddress);
}

void BackupManager::removeBackupServer(Address serverAddress) {
    for (int i = 0; i<serverAddresses.size(); i++) {
        if (serverAddresses[i] == serverAddress) 
            getBackupServerAddresses().erase(serverAddresses.begin() + i);
    }
}

bool BackupManager::isPrimaryServer() {
    return BackupManager::isPrimary;
}

void BackupManager::setServerAsPrimary() {
    BackupManager::isPrimary = true;
}

void BackupManager::setPrimaryServerAddress(Address address) {
    BackupManager::primaryServerAddress = address;
}

Address BackupManager::getPrimaryServerAddress() {
    return BackupManager::primaryServerAddress;
}

vector<Address> BackupManager::getBackupServerAddresses() {
    return BackupManager::serverAddresses;
}

string BackupManager::getBackupServers(){
    string line;
    for (auto & serverAddress : serverAddresses) {
        if (serverAddress == serverAddresses[0])
            line += addressToString(serverAddress);
        else
            line += "," + addressToString(serverAddress);
    }
    return line;
}