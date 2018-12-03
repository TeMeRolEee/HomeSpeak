#include <QtCore/QDataStream>
#include <QtCore/QJsonDocument>
#include <QHostAddress>
#include "tcpserverthread.h"



TcpServerThread::TcpServerThread(QTcpSocket *socket, int id) : socket(socket),
    id(id) {

}

void TcpServerThread::sendMessage_slot(const QJsonObject &messageData) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

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

    //socket->write(data);

    emit messageRecieved_signal(data, id);

    this->exec();
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
