#pragma once

#include <QThread>
#include <QUuid>

#include "tcpserver.h"

class Core : public QThread {
public:
	Core();

	~Core() override;

	void init();

protected:
	void run() override;

private:
	bool readSettings(const QString &filePath);

	TcpServer *tcpServer;

public slots:

	void startTcpServer_slot();

signals:
	void startTcpServer_signal();
};


