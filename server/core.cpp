#include "core.h"

#include "messagetypes.h"

Core::Core() {
    tcpServer = new TcpServer();
}

Core::~Core() {
    delete tcpServer;
}


