#pragma once

#include "Communication/CommunicationManager.h" //TODO: replace with Address.h
#include "Communication/Packet.h"

class Interface {
public:
    static void serverStart(bool isPrimary);
    static void informReceivedPacket(Packet packet, Address address, bool isPrimary);
    static void informSuccessfulRequest(Packet packet);
};
