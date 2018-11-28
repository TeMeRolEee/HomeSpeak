cmake_minimum_required(VERSION 3.1)
project(server)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core HINTS ~/Qt/5.11.1/gcc_64/)
find_package(Qt5Sql HINTS ~/Qt/5.11.1/gcc_64)
find_package(Qt5Network HINTS ~/Qt/5.11.1/gcc_64)

add_executable(server main.cpp core.cpp dbmanager.cpp tcpserver.cpp client.cpp handlecommunication.cpp messagetypes.h jsonparser.cpp loglevels.h logger.cpp tcpserverthread.cpp)

# linking
target_link_libraries(server Qt5::Core Qt5::Sql Qt5::Network)