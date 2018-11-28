#include <QtNetwork>
#include <QtCore>
#include <QDebug>
#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QObject(parent) {
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &TcpServer::newConnection_slot);

    clients = new QMap<int, TcpServerThread*>();

    if (!server->listen(QHostAddress::AnyIPv4, 8086)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started successfully!";
    }
}

void TcpServer::newConnection_slot() {
    QTcpSocket *socket = server->nextPendingConnection();

    auto *thread = new TcpServerThread();

    clients->insert(clientCounter++, thread);

    connect(thread, &TcpServerThread::messageRecieved_signal, this, &TcpServer::newDataRecieved_signal);

    thread->setSocket(server->nextPendingConnection());

    thread->run();

    //socket->close();
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

void TcpServer::getMessageFromThread_slot(const QByteArray data) {
    emit newDataRecieved_signal(data);
}

void TcpServer::sendMessage_slot(const QJsonObject &message) {

}
