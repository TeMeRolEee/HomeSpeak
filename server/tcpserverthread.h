#pragma once

#include <QtCore/QThread>
#include <QTcpSocket>
#include <QHostAddress>

class TcpServerThread : public QThread {
Q_OBJECT

public:
    TcpServerThread(QTcpSocket *socket, int id);
    ~TcpServerThread();

    void setNewSocket(QTcpSocket *socket);

    void run() override;

    int getId();

    QHostAddress getIpAddress();

private:
    QTcpSocket *socket;

    int id;

    QHostAddress address;


public slots:
    void sendMessage_slot(const QJsonObject &messageData);

signals:
    void messageRecieved_signal(QByteArray data, int id);

    void sendMessage_signal(const QJsonObject &messageData);

    void clientDisconnected_signal();
};


