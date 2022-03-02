#pragma once
#include "ProfileSessionManager.h"
#include "CommunicationManager.h"
#include "NotificationManager.h"

class Server{
    private:
        NotificationManager notificationManager;
        CommunicationManager communicationManager;
        ProfileSessionManager profileSessionManager;
    public:

};
