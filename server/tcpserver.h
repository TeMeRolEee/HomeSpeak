#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class TcpServer : public QObject {
    Q_OBJECT

public:
    explicit TcpServer(QObject * parent = nullptr);
    ~TcpServer();

signals:
	void newDataRecieved_signal(QByteArray data);

public slots:
    void newConnection_slot();

private:
    QTcpServer *server = nullptr;
    QVector<QHostAddress*> *clientVector;

    void storeIp(const QHostAddress &ipAddress);

    bool checkIpExists(const QHostAddress &ipAddress);
};
