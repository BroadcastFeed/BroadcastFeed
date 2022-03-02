#pragma once
#include "Profile.h"
#include "Notification.h"

class NotificationManager{
    private:
    public:
        void sendNotification(Notification notification, Profile user);
        void recieveNotification (Notification notification, Profile user);
};