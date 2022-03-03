cmake_minimum_required(VERSION 3.16.3)
project(server)

set(CMAKE_CXX_STANDARD 20)

add_executable(server src/main.cpp src/Server.cpp src/Communication/Communication.cpp, src/Communication/Packet.cpp src/Database/Database.cpp,
        src/Notification/Notification.cpp, src/Notification/NotificationManager.cpp, src/Profile/Profile.cpp,
        src/Session/ProfileSessionManager.cpp)
