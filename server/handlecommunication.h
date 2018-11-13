#pragma once

#include <QtCore/QObject>
#include "jsonparser.h"
#include "dbmanager.h"

class HandleCommunication : public QObject {
Q_OBJECT

public:
	HandleCommunication();
	~HandleCommunication() override;

private:
	DBManager *dbManager;

	JsonParser *jsonParser;

	void handleConnectionRequest(const QJsonObject &messageData);

	void handleDisconnection(const QJsonObject &messageData);

	void handleTextMessage(const QJsonObject &messageData);

	void handleSwitchRoom(const QJsonObject &messageData);

	void handleMicMuteNotification(const QJsonObject &messageData);

	void handleMicUnMuteNotification(const QJsonObject &messageData);

	void handleSpeakerMuteNotification(const QJsonObject &messageData);

	void handleSpeakerUnMuteNotification(const QJsonObject &messageData);

	void handleRegistrationRequest(const QJsonObject &messageData);

public slots:

	void parseJson_slot(const QByteArray &messageData);

	void processMessage_slot(const QJsonObject &messageData);

signals:

	void parsingDone_signal(const QJsonObject &messageData);

	void processMessageDone_signal(int returnCode);
};

