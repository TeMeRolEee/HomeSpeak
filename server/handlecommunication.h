#pragma once

#include <QtCore/QObject>

class HandleCommunication : public QObject {
Q_OBJECT

public:


private:
	void handleConnectionRequest(const QJsonObject &messageData);

	void handleDisconnection(const QJsonObject &messageData);

	void handleTextMessage(const QJsonObject &messageData);

	void handleSwitchRoom(const QJsonObject &messageData);

	void handleMicMuteNotification(const QJsonObject &messageData);

	void handleMicUnMuteNotification(const QJsonObject &messageData);

	void handleSpeakerMuteNotification(const QJsonObject &messageData);

	void handleSpeakerUnMuteNotification(const QJsonObject &messageData);

public slots:

	void parseJson_slot(const QByteArray &messageData);

	void processMessage_slot(const QJsonObject &messageData);

signals:

	void parsingDone_signal(const QJsonObject &messageData);

	void processMessageDone_signal(int returnCode);
};

