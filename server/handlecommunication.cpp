#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include "handlecommunication.h"

#include "messagetypes.h"
#include "jsonparser.h"


void HandleCommunication::parseJson_slot(const QByteArray &messageData) {
	JsonParser jsonParser;
	QJsonObject messageObject = jsonParser.parseJson(messageData);
}

void HandleCommunication::processMessage_slot(const QJsonObject &messageData) {
	switch (messageData.value("type").toInt()) {
		case static_cast<int>(MessageTypes::CONNECTION_REQUEST):
			handleConnectionRequest(messageData);
			break;
		case static_cast<int>(MessageTypes::DISCONNECT):
			handleDisconnection(messageData);
			break;
		case static_cast<int>(MessageTypes::TEXT_MESSAGE):
			handleTextMessage(messageData);
			break;
		case static_cast<int>(MessageTypes::VOICE_MESSAGE):
			break;
		case static_cast<int>(MessageTypes::SWITCH_ROOM):
			handleSwitchRoom(messageData);
			break;
		case static_cast<int>(MessageTypes::MIC_MUTE_NOTIFICATION):
			handleMicMuteNotification(messageData);
			break;
		case static_cast<int>(MessageTypes::MIC_UNMUTE_NOTIFICATION):
			handleMicUnMuteNotification(messageData);
			break;
		case static_cast<int>(MessageTypes::SPEAKER_MUTE_NOTIFICATION):
			handleSpeakerMuteNotification(messageData);
			break;
		case static_cast<int>(MessageTypes::SPEAKER_UNMUTE_NOTIFICATION):
			handleSpeakerUnMuteNotification(messageData);
			break;
        case static_cast<int>(MessageTypes ::REGISTRATION_REQUEST):
            break;
		default:break;
	}
}

void HandleCommunication::handleConnectionRequest(const QJsonObject &messageData) {
	//TODO finish function!
}

void HandleCommunication::handleDisconnection(const QJsonObject &messageData) {
	//TODO finish function!
}

void HandleCommunication::handleTextMessage(const QJsonObject &messageData) {

}

void HandleCommunication::handleSwitchRoom(const QJsonObject &messageData) {
	//TODO finish function!
}

void HandleCommunication::handleMicMuteNotification(const QJsonObject &messageData) {
 	//TODO finish function!
}

void HandleCommunication::handleMicUnMuteNotification(const QJsonObject &messageData) {
	//TODO finish function!
}

void HandleCommunication::handleSpeakerMuteNotification(const QJsonObject &messageData) {
	//TODO finish function!
}

void HandleCommunication::handleSpeakerUnMuteNotification(const QJsonObject &messageData) {
	//TODO finish function!
}
