#include <QtCore/QJsonDocument>

#include "jsonparser.h"

QJsonObject JsonParser::parseJson(const QByteArray &inputArray) {
	QJsonObject messageObject = QJsonDocument::fromBinaryData(inputArray).object();

	if (!messageObject.isEmpty()) {
		return messageObject;
	}

	return QJsonObject();
}
