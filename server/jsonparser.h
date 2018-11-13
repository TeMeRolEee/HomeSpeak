#pragma once

#include <QtCore/QJsonObject>

class JsonParser {
public:
	QJsonObject parseJson(const QByteArray &inputArray);
};


