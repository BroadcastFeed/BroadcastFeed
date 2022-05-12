#include "Interface.h"

#include <iostream>

using std::cout;
using std::endl;

void Interface::serverStart(bool isPrimary)
{
    cout << "Server running, press Ctrl-C to save and exit." << endl;
    if (!isPrimary)
        cout << "RUNNING IN BACKUP MODE" << endl;

}

void Interface::informReceivedPacket(Packet packet, Address address, bool isPrimary) {
    string user = packet.getUsername();
    if(!user.empty()){
        cout << "User " << packet.getUsername() << " "; 
        if(isPrimary){
            cout << "requests ";
        } 
    } else {
       //TODO: print address 
    }
    cout << PACKET_TYPE_NAMES[packet.getType()];
    string message = packet.getMessage();
    if(!message.empty()){
        cout << " \"" << message << "\"";
    }
    cout << endl;
}

void Interface::informSuccessfulRequest(Packet packet) {
    cout << "REQUEST SUCCESSFUL: " << packet.getUsername() << endl;
}