#include <QtCore/QDataStream>
#include <QtCore/QJsonDocument>
#include <QHostAddress>
#include <QtCore/QJsonObject>
#include <QtCore/QCryptographicHash>
#include <QtCore/QJsonArray>
#include "tcpserverthread.h"



TcpServerThread::TcpServerThread(QTcpSocket *socket, int id) : socket(socket),
    id(id) {

}

void TcpServerThread::sendMessage_slot(const QJsonObject &messageData) {
    socket->open(QIODevice::WriteOnly);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    for (auto data : messageData.keys()) {
        qDebug() << messageData.value(data) << "is about to be sent";
    }

    out << messageData;

    while (!socket->isWritable()) {
    }
    if (socket->isWritable()) {
        socket->write(block);
    }
}

void TcpServerThread::run() {
    address = socket->peerAddress();
    QByteArray data;

    qDebug() << "New user" << QThread::currentThreadId() << id;

    qDebug() <<  socket->peerAddress().toString() << socket->isOpen();

    qDebug() << socket->bytesAvailable();

    socket->waitForBytesWritten();
    socket->waitForReadyRead();

    while (data.size() < socket->bytesAvailable()) {

        data += socket->readAll();
        qDebug() << data;
    }

    qDebug() << "Total message" << data;

    QJsonObject messageObject = QJsonDocument::fromJson(data).object();

    QJsonObject response;
    response.insert("type", 0);
    response.insert("status", 1);

    QJsonArray dataArray;

    QJsonObject tokenObject;

    //QString id(dbManager->getUserID(messageData.value("email").toString()));
    QString id(QCryptographicHash::hash(messageObject.value("email").toString().toUtf8(), QCryptographicHash::Sha3_256));
    QString token = QCryptographicHash::hash(id.toUtf8(), QCryptographicHash::Sha3_256);

    tokenObject.insert("token", token);

    dataArray.append(tokenObject);

    QJsonArray rooms;

    QJsonObject room0;

    room0.insert("roomID", 0);

    QJsonArray users;// = dbManager->getOnlineUsers();

    room0.insert("users", users);

    rooms.append(room0);

    response.insert("token", tokenObject);

    response.insert("rooms", rooms);

    response.insert("users", users);

    QJsonDocument document(response);

    socket->write(document.toJson());

    //emit messageRecieved_signal(data, id);

    //this->exec();
    //socket->flush();
/*
    while (socket->isOpen()) {
        qDebug() << "doing something";
        //socket->waitForBytesWritten();
        qDebug() << "doing something2";
        //socket->waitForReadyRead();
        qDebug() << "doing something3";
        data.clear();

        data += socket->readAll();
        qDebug() << "doing something4";
        emit messageRecieved_signal(data, id);
        if (!data.isEmpty()) {
            while (!socket->isWritable()) {
                qDebug() << "waiting...";
            }
            socket->write(data);
            socket->waitForBytesWritten();
            qDebug() << "Total message" << data;
            //socket->close();
        }
    }*/




}

TcpServerThread::~TcpServerThread() {
    delete socket;
}

void TcpServerThread::setNewSocket(QTcpSocket *socket) {
    socket = socket;
}

int TcpServerThread::getId() {
    return id;
}

QHostAddress TcpServerThread::getIpAddress() {
    return address;
}
