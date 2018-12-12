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
    clientVector = new QMap<int, QHostAddress*>();

    if (!server->listen(QHostAddress::AnyIPv4, 8086)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started successfully!";
    }
}

void TcpServer::newConnection_slot() {
    QTcpSocket *socket = server->nextPendingConnection();

    int id = checkIpExists(socket->peerAddress());
    storeIp(socket->peerAddress(),clientCounter++);

    if (id) {
        //clients->value(id)->wait();
        //clients->value(id)->quit();

        auto *thread = new TcpServerThread(socket, id);

        delete clients->take(id);

        clients->insert(id, thread);

        clients->value(id)->run();
        //clients->value(id)->start();
    } else {
        auto *thread = new TcpServerThread(socket, clientCounter);

        clients->insert(clientCounter, thread);

        connect(thread, &TcpServerThread::messageRecieved_signal, this, &TcpServer::getMessageFromThread_slot);
        connect(thread, &TcpServerThread::sendMessage_signal, thread, &TcpServerThread::sendMessage_slot);
        connect(this, &TcpServer::sendMessage_signal, thread, &TcpServerThread::sendMessage_slot);


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

void TcpServer::storeIp(const QHostAddress &ipAddress, int id) {
    if (!checkIpExists(ipAddress)) {
        auto *hostAddress = new QHostAddress();
        hostAddress->setAddress(ipAddress.toIPv4Address());
        clientVector->insert(id, hostAddress);
    }
}

bool TcpServer::checkIpExists(const QHostAddress &ipAddress) {
    for (auto ip : clientVector->keys()) {
        if (*clientVector->value(ip) == ipAddress) {
            return true;
        }
    }
    return false;
}

void TcpServer::getMessageFromThread_slot(const QByteArray data, int id) {
    emit newDataRecieved_signal(data, id);
}

void TcpServer::sendMessage_slot(const QJsonObject &messageData, int id) {
    qDebug() << messageData.keys();
/*
    for (auto user : clientVector->keys()) {
        qDebug() << *clientVector->value(user);
        if (user != id) {
            auto *socket = new QTcpSocket();

            socket->connectToHost(*clientVector->value(user), 8086);
            qDebug() << *clientVector->value(user);
            socket->open(QIODevice::WriteOnly);
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);

            QJsonDocument document(messageData);

            QByteArray array = document.toJson();

            out << array;

            socket->write(block);
            //while (!socket->isWritable()) {
            //}
            if (socket->isWritable()) {

            }
        }

    }
*/
    emit clients->value(id)->sendMessage_signal(messageData);
}

void TcpServer::sendMessageToUsers_slot(const QJsonObject &message, int id) {
    for (auto thread : clients->keys()) {
        if (clients->value(thread)->getId() != id) {
            qDebug() << "motherfucker" << clients->value(thread)->getId();
            emit clients->value(thread)->sendMessage_slot(message);
        }
    }
}
