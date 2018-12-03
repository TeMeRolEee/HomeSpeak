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

	void handleConnectionRequest(const QJsonObject &messageData, int user);

	void handleDisconnection(const QJsonObject &messageData, int user);

	void handleTextMessage(const QJsonObject &messageData, int user);

	void handleSwitchRoom(const QJsonObject &messageData, int user);

	void handleMicMuteNotification(const QJsonObject &messageData, int user);

	void handleMicUnMuteNotification(const QJsonObject &messageData, int user);

	void handleSpeakerMuteNotification(const QJsonObject &messageData, int user);

	void handleSpeakerUnMuteNotification(const QJsonObject &messageData, int user);

	void handleRegistrationRequest(const QJsonObject &messageData, int user);

public slots:

	void parseJson_slot(const QByteArray &messageData, int user);

	void processMessage_slot(const QJsonObject &messageData, int user);

	void sendResponse(const QJsonObject &messageData, int user);

signals:

	void parsingDone_signal(const QJsonObject &messageData, int user);

	void processMessageDone_signal(int returnCode);
};

