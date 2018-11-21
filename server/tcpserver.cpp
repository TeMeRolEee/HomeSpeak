#include <QtNetwork>
#include <QtCore>
#include <QDebug>
#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QObject(parent) {
    server = new QTcpServer(this);
    clientVector = new QVector<QHostAddress*>();

    connect(server, &QTcpServer::newConnection, this, &TcpServer::newConnection_slot);

    if (!server->listen(QHostAddress::AnyIPv4, 8085)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started successfully!";
    }
}

void TcpServer::newConnection_slot() {
    QTcpSocket *socket = server->nextPendingConnection();
    QByteArray data;

    while (!data.contains("\n")) {
        socket->waitForReadyRead();
        data += socket->readAll();
    }

    storeIp(socket->peerAddress());

    emit newDataRecieved_signal(data);

    socket->write(data);
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close();
}

TcpServer::~TcpServer() {
    delete server;
    delete clientVector;
}

void TcpServer::storeIp(const QHostAddress &ipAddress) {
    if (!checkIpExists(ipAddress)) {
        //clientVector->append(ipAddress);
    }
}

bool TcpServer::checkIpExists(const QHostAddress &ipAddress) {
    /*for (auto i : *clientVector) {
        if (i->toIPv4Address() == ipAddress.toIPv4Address()) {
            return true;
        }
    }*/
    return false;
}
