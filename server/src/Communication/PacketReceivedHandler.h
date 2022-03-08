#pragma once

#include<thread>
#include "../Communication/Packet.h"

class PacketReceivedHandler {
public:
    void handle(Packet packet);
};
