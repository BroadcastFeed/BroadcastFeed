#include <iostream>
#include "Server.h"

Server::Server(char *ipAddress, unsigned int port) : communicationManager(ipAddress, port) {}

void Server::listen(int sequenceNumber, int64_t timestamp) {
    pair<Packet, Address> received = communicationManager.listen(sequenceNumber, timestamp);

    thread handleThread(handlePacket, received.first, received.second);
    handleThread.detach();
    threads.push_back(move(handleThread));
    openedThreads.insert({handleThread.get_id(), move(handleThread)});
}

void Server::handlePacket(const Packet& packet, Address received) {
    cout << "New thread " << endl;
    cout << "Packet received " << (string) packet << endl;

    std::this_thread::sleep_for(std::chrono::seconds(20000));

    cout << "I'm killing myself" << endl;
    erase_if(threads, [](thread& th) {return th.get_id() == std::this_thread::get_id();});
//    openedThreads.erase(std::this_thread::get_id());
//    int pendingReaders = -1;
//    Notification notification = Notification(0, 0, 0, 0, "");
//    switch (packet.getType()) {
//        case CONNECT: {
//            ProfileSessionManager::registerNewSession(packet.getMessage(), received);
//            ProfileSessionManager::getOpenedSessions(packet.getUsername());
//            break;
//        }
//        case SEND:
//            //pendingReaders = packet.getFollowers().length();
//            notification = Notification(packet.getSeqNum(), packet.getTimestamp(),
//                                        packet.getLength(), pendingReaders,
//                                        packet.getMessage());
//            ProfileSessionManager::addNotification(packet.getUsername(), notification);
//
//            break;
//
//        case FOLLOW:
//            ProfileSessionManager::addFollower(packet.getMessage(), packet.getUsername());
//
//            break;
//
//        case DISCONNECT:
//
//            break;
//
//        default:
//
//            return;
//    }
}

void Server::halt() {
    shutdown(communicationManager.getDescriptor(), SHUT_RDWR);

    cout << "Waiting threads to finish..." << endl;
    for (thread &th : threads) {
        if (th.joinable()) {
            cout << th.get_id() << " is joinable" << endl;
            th.join();
        } else {
            cout << th.get_id() << " is not joinable" << endl;
        }
    }
}
