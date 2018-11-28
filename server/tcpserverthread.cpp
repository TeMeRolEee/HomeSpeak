#include <QtCore/QDataStream>
#include <QtCore/QJsonDocument>
#include "tcpserverthread.h"



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
    socket = new QTcpSocket();

    qDebug() << "New user";
    while (socket->isOpen()) {
        QByteArray data;

        socket->waitForReadyRead();

        qDebug() << socket->bytesAvailable();

        while (data.size() < socket->bytesAvailable()) {

            data += socket->readAll();
            qDebug() << data;
        }

        qDebug() << "Total message" << data;

        emit messageRecieved_signal(data);

        socket->write(data);

        socket->flush();

        socket->waitForBytesWritten();
    }


    //socket->waitForDisconnected();
}

void TcpServerThread::setSocket(QTcpSocket *socket) {
    socket = socket;
}
