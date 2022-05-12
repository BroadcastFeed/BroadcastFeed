//
// Created by wmespindula on 12/05/22.
//

#ifndef SERVER_SERVERPINGSERVICE_H
#define SERVER_SERVERPINGSERVICE_H


#include "CommunicationManager.h"
#include "../Server.h"

class ServerPingService {
private:
    CommunicationManager communicationManager;
    Server serverInstance;

    volatile bool checkingPrimaryServerRunning;
    volatile bool checkingBackupServersRunning;

    volatile int checkingPrimaryFrequency;
    volatile int checkingBackupsFrequency;

    void runCheckingPrimary();
    void runCheckingBackups();
public:
    ServerPingService(CommunicationManager communicationManager, Server server);
    void startCheckingPrimary(int frequency);
    void stopCheckingPrimary();

    void startCheckingBackups(int frequency);
    void stopCheckingBackups();

    void callbackElection();
};


#endif //SERVER_SERVERPINGSERVICE_H
