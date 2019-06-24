cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Network REQUIRED)

add_executable(server main.cpp core.cpp dbmanager.cpp tcpserver.cpp)

# linking
target_link_libraries(server Qt5::Core Qt5::Sql Qt5::Network)
