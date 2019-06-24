#include "core.h"

Core::Core() {
}

Core::~Core() {
	delete tcpServer;
}

void Core::run() {
	QThread::run();
}

void Core::init() {
	tcpServer = new TcpServer();
}

bool Core::readSettings(const QString &filePath) {
	return false;
}

void Core::startTcpServer_slot() {

}


