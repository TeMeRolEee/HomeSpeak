#pragma once

#include <QtCore/QObject>

class HandleCommunication : public QObject {
Q_OBJECT

public:


private:

public slots:
	void parseJson_slot(QByteArray messageData);

signals:
	void notifyCore_signal(int messageType, QJsonObject messageData);
};

