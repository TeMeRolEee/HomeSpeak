#pragma once

#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include "tcpserverthread.h"

class TcpServer : public QObject {
    Q_OBJECT

public:
    explicit TcpServer(QObject * parent = nullptr);
    ~TcpServer();

signals:
	void newDataRecieved_signal(QByteArray data, int id);

	void sendMessage_signal(const QJsonObject &messageData);

public slots:
    void newConnection_slot();

    void sendMessage_slot(const QJsonObject &message, int id);

    void getMessageFromThread_slot(QByteArray data, int id);

private:
    QTcpServer *server = nullptr;
    QMap<int, TcpServerThread*> *clients;
    QVector<QHostAddress*> *clientVector;
    int clientCounter = 0;

    void storeIp(const QHostAddress &ipAddress);

    int checkIpExists(const QHostAddress &ipAddress);

};
