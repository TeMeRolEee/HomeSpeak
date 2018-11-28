#pragma once

#include <QtCore/QThread>
#include <QTcpSocket>

class TcpServerThread : public QThread {
Q_OBJECT

public:
    void run() override;

    void setSocket(QTcpSocket *socket);

private:
    QTcpSocket *socket;


public slots:
    void sendMessage_slot(const QJsonObject &messageData);

signals:
    void messageRecieved_signal(QByteArray data);

    void clientDisconnected_signal();
};


