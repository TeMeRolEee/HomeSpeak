#include <QtNetwork>
#include <QtCore>
#include <QDebug>
#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QObject(parent) {
    qDebug() << QThread::currentThreadId();
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

    int id = checkIpExists(socket->peerAddress());
    if (id != -1) {
        //clients->value(id)->wait();
        //clients->value(id)->quit();

        auto *thread = new TcpServerThread(socket, id);

        delete clients->take(id);

        clients->insert(id, thread);

        clients->value(id)->run();
        //clients->value(id)->start();
    } else {
        auto *thread = new TcpServerThread(socket, clientCounter++);

        clients->insert(clientCounter, thread);

        connect(thread, &TcpServerThread::messageRecieved_signal, this, &TcpServer::newDataRecieved_signal);

        //thread->start();
        thread->run();
    }

    qDebug() << "rungdsgsd";

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

int TcpServer::checkIpExists(const QHostAddress &ipAddress) {
    for (auto thread : clients->keys()) {
        if (clients->value(thread)->getIpAddress() == ipAddress) {
            return clients->value(thread)->getId();
        }
    }
    return -1;
}

void TcpServer::getMessageFromThread_slot(const QByteArray data, int id) {
    emit newDataRecieved_signal(data, id);
}

void TcpServer::sendMessage_slot(const QJsonObject &message, int id) {

}
