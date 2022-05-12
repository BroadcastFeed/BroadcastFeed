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
    //TODO: implement
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