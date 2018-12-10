#include "core.h"

#include "messagetypes.h"
#include "loglevels.h"

Core::Core() {
	tcpServer = new TcpServer();
	communicationHandler = new HandleCommunication();

	connect(tcpServer, &TcpServer::newDataRecieved_signal, communicationHandler, &HandleCommunication::parseJson_slot);
	connect(communicationHandler, &HandleCommunication::parsingDone_signal, communicationHandler,
			&HandleCommunication::processMessage_slot);
	connect(communicationHandler, &HandleCommunication::processMessageDone_signal, this, &Core::processMessageAck_slot);
	connect(communicationHandler, &HandleCommunication::sendResponse_signal, tcpServer, &TcpServer::sendMessage_slot);
	connect(communicationHandler, &HandleCommunication::responseMessageReady_signal, tcpServer, &TcpServer::sendMessageToUsers_slot);
}

Core::~Core() {
	delete tcpServer;
	delete communicationHandler;
}

void Core::processMessageAck_slot(int returnCode) {
	switch (returnCode) {
		case static_cast<int>(LogLevel::INFO):
			break;
		case static_cast<int>(LogLevel::DEBUG):
			break;
		case static_cast<int>(LogLevel::WARNING):
			break;
		case static_cast<int>(LogLevel::CRITICAL):
			break;
		default:
			break;
	}


}


