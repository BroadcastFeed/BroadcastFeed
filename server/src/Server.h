#pragma once

#include "Session/ProfileSessionManager.h"
#include "Communication/CommunicationManager.h"
#include "Notification/NotificationManager.h"

class Server {
private:
    NotificationManager notificationManager;
    CommunicationManager communicationManager;
    ProfileSessionManager profileSessionManager;
public:

};
