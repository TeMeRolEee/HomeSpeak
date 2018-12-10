#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>

#include "handlecommunication.h"
#include "messagetypes.h"
#include "jsonparser.h"
#include "loglevels.h"


HandleCommunication::HandleCommunication() {
	jsonParser = new JsonParser();
	dbManager = new DBManager("server.sqlite");
	dbManager->initDataBase();

	connect(this, &HandleCommunication::parsingDone_signal, this, &HandleCommunication::processMessage_slot);
}

HandleCommunication::~HandleCommunication() {
	delete jsonParser;
	delete dbManager;
}

void HandleCommunication::parseJson_slot(const QByteArray &messageData, int user) {
	emit parsingDone_signal(jsonParser->parseJson(messageData), user);
}

void HandleCommunication::processMessage_slot(const QJsonObject &messageData, int user) {
	switch (messageData.value("type").toInt()) {
		case static_cast<int>(MessageTypes::CONNECTION_REQUEST):
			handleConnectionRequest(messageData, user);
			break;
		case static_cast<int>(MessageTypes::DISCONNECT):
			handleDisconnection(messageData, user);
			break;
		case static_cast<int>(MessageTypes::TEXT_MESSAGE):
			handleTextMessage(messageData, user);
			break;
		case static_cast<int>(MessageTypes::VOICE_MESSAGE):
			break;
		case static_cast<int>(MessageTypes::SWITCH_ROOM):
			handleSwitchRoom(messageData, user);
			break;
		case static_cast<int>(MessageTypes::MIC_MUTE_NOTIFICATION):
			handleMicMuteNotification(messageData, user);
			break;
		case static_cast<int>(MessageTypes::MIC_UNMUTE_NOTIFICATION):
			handleMicUnMuteNotification(messageData, user);
			break;
		case static_cast<int>(MessageTypes::SPEAKER_MUTE_NOTIFICATION):
			handleSpeakerMuteNotification(messageData, user);
			break;
		case static_cast<int>(MessageTypes::SPEAKER_UNMUTE_NOTIFICATION):
			handleSpeakerUnMuteNotification(messageData, user);
			break;
		case static_cast<int>(MessageTypes::REGISTRATION_REQUEST):
			handleRegistrationRequest(messageData, user);
			break;
		default:
			break;
	}
}

void HandleCommunication::handleConnectionRequest(const QJsonObject &messageData, int user) {
    if (dbManager->checkUserEmail(messageData.value("email").toString()) &&
    dbManager->checkPassword(messageData.value("email").toString(), messageData.value("password").toString())) {
        QJsonObject response;
        response.insert("type", 0);
        response.insert("status", 1);
        QJsonArray dataArray;

        QJsonObject tokenObject;

		QString id(dbManager->getUserID(messageData.value("email").toString()));

        QString token = QCryptographicHash::hash(id.toUtf8(), QCryptographicHash::Sha3_256);

        tokenObject.insert("token", token);

        dataArray.append(tokenObject);

        QJsonArray rooms;

        QJsonObject room0;

        room0.insert("roomID", 0);

        QJsonArray users = dbManager->getOnlineUsers();

        room0.insert("users", users);

        rooms.append(room0);

        dbManager->addToOnlineUsers(id.toInt(), 0);

        emit sendResponse_signal(response, user);
    }
}


void HandleCommunication::handleDisconnection(const QJsonObject &messageData, int user) {
	//TODO finish function!
}

void HandleCommunication::handleTextMessage(const QJsonObject &messageData, int user) {
    emit responseMessageReady_signal(messageData, user);
}

void HandleCommunication::handleSwitchRoom(const QJsonObject &messageData, int user) {

	//TODO finish function!
}

void HandleCommunication::handleMicMuteNotification(const QJsonObject &messageData, int user) {
	//TODO finish function!
}

void HandleCommunication::handleMicUnMuteNotification(const QJsonObject &messageData, int user) {
	//TODO finish function!
}

void HandleCommunication::handleSpeakerMuteNotification(const QJsonObject &messageData, int user) {
	//TODO finish function!
}

void HandleCommunication::handleSpeakerUnMuteNotification(const QJsonObject &messageData, int user) {
	//TODO finish function!
}

void HandleCommunication::handleRegistrationRequest(const QJsonObject &messageData, int user) {
	if (!messageData.empty()) {
		QString nickname, email, password;

		nickname = messageData.value("nickname").toString();
		email = messageData.value("email").toString();
		password = messageData.value("password").toString();

		emit processMessageDone_signal(dbManager->registerUser(email, password, nickname));
	}

	emit processMessageDone_signal(static_cast<int>(LogLevel::CRITICAL));
}
