//
// Created by wmespindula on 12/05/22.
//

#include <thread>
#include <iostream>
#include "ServerPingService.h"
#include "Address.h"
#include "../BackupManager.h"


ServerPingService::ServerPingService(CommunicationManager communicationManager, Server server)
        : communicationManager(communicationManager), serverInstance(server){};

void ServerPingService::runCheckingPrimary() {
    std::cout << "Checking primary server... " << std::endl;
    Address primaryServer = BackupManager::getPrimaryServerAddress();
    int frequency = checkingPrimaryFrequency;
    std::thread pingThread([this, primaryServer, frequency] {
        while (this->checkingPrimaryServerRunning) {
            std::cout << "Checking primary server Reachability... " << std::endl;
            bool reachable = this->communicationManager.isReachable(primaryServer);
            std::cout << "The primary server" << primaryServer << "is" << (!reachable ? "not" : "") << " reachable " << std::endl;
            if (!reachable) {
                this->callbackElection();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(frequency));
        };
    });
    pingThread.detach();
}

void ServerPingService::runCheckingBackups() {
    std::cout << "Checking backup nodes... " << std::endl;
    vector <Address> backupServers = BackupManager::getBackupServerAddresses();
    int frequency = checkingBackupsFrequency;
    std::thread pingThread([this, backupServers, frequency] {
        while (this->checkingBackupServersRunning) {
            std::cout << "Checking primary server Reachability... " << std::endl;
            for (Address backupServer: backupServers) {
                bool reachable = this->communicationManager.isReachable(backupServer);
                std::cout << "The backup server" << backupServer << "is" << (!reachable ? "not" : "") << " reachable "
                          << std::endl;
                if (!reachable) {
                    std::cout << "Updating it!" << std::endl;
                    BackupManager::removeBackupServer(backupServer);
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(frequency));
        };
    });
    pingThread.detach();
}

void ServerPingService::startCheckingPrimary(int frequency) {
    this->checkingPrimaryServerRunning = true;
    this->checkingPrimaryFrequency = frequency;
    runCheckingPrimary();
}

void ServerPingService::stopCheckingPrimary() {
    this->checkingPrimaryServerRunning = false;
}

void ServerPingService::startCheckingBackups(int frequency) {
    this->checkingBackupServersRunning = true;
    this->checkingBackupsFrequency = frequency;
    runCheckingBackups();
}
void ServerPingService::stopCheckingBackups() {
    this->checkingPrimaryServerRunning = false;
}

void ServerPingService::callbackElection() {
    this->serverInstance.election();
}
