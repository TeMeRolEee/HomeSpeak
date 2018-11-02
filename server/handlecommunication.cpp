#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include "handlecommunication.h"

#include "messagetypes.h"


void HandleCommunication::parseJson_slot(QByteArray messageData) {
	QJsonObject messageObject = QJsonDocument::fromBinaryData(messageData).object();
}
