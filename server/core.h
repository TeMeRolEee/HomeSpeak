#pragma once

#include "tcpserver.h"
#include "handlecommunication.h"
#include "dbmanager.h"

class Core : public QObject {
	Q_OBJECT
public:
    Core();
    ~Core();
    TcpServer *tcpServer;
    HandleCommunication *communicationHandler;

private:


public slots:

	void processMessageAck_slot(int returnCode);

signals:

};


