#include <QtCore/QJsonDocument>
#include <QDebug>

#include "jsonparser.h"

QJsonObject JsonParser::parseJson(const QByteArray &inputArray) {
	QString input = "";

	for (auto character : inputArray) {
		//qDebug() << character;
		if (character != '\\') {
			input += character;
		}
	}

	QJsonObject messageObject = QJsonDocument::fromJson(input.toUtf8()).object();
	qDebug() << messageObject.keys() << "string" << input;

	//for (const auto &key : messageObject.keys()) {
	//	qDebug() << "key:" << messageObject.value(key);
	//}

	if (!messageObject.isEmpty()) {
		return messageObject;
	}

	return QJsonObject();
}
