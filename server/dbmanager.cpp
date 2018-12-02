#include <QtSql/QSqlQuery>
#include <QtCore/QVector>
#include "dbmanager.h"

DBManager::DBManager(const QString &path) : dataBaseFilePath(path) {
}

bool DBManager::initDataBase() {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(dataBaseFilePath);

	QSqlQuery createUsersTableQuery("CREATE TABLE `users` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, `name` TEXT NOT NULL, `email` TEXT NOT NULL UNIQUE, `password` TEXT NOT NULL UNIQUE )");

	QSqlQuery createOnlineUsersQuery("CREATE TABLE `onlineUsers` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `userID` INTEGER NOT NULL UNIQUE, `roomID` INTEGER NOT NULL )");

	QSqlQuery createRoomsUsersQuery("CREATE TABLE `rooms` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `roomName` TEXT NOT NULL )");

	if (database.open() &&
			createUsersTableQuery.exec() &&
			createOnlineUsersQuery.exec() &&
			createRoomsUsersQuery.exec()) {
		database.close();
		return true;
	}
	return false;
}

bool DBManager::checkUserIDExists(const QString &id) {
	if (database.open()) {
		if (!id.isEmpty()) {
			QSqlQuery qSqlQuery;
			qSqlQuery.prepare("SELECT id FROM users WHERE id = (:id)");
			qSqlQuery.bindValue(":id", id);

			database.close();
			return qSqlQuery.exec() && qSqlQuery.next();
		}

		database.close();
	}
    return false;
}

int DBManager::getUsersRoomId(const int &id) {

	if (database.open()) {
//TODO FINISH UP THIS FUNCTION!
		if (id >= 0) {
			QSqlQuery qSqlQuery;
			qSqlQuery.prepare("SELECT roomID FROM ");

			return 0;
		}

		database.close();
	}
}

int DBManager::registerUser(const QString &email, const QString &password, const QString &nickName) {
	if (database.open()) {
		if (!email.isEmpty() && !password.isEmpty() && !nickName.isEmpty()) {
			if (!checkUserEmail(email) && checkUserNickName(nickName)) {
				QSqlQuery qSqlQuery;

				qSqlQuery.prepare("INSERT INTO users (name, email, password) VALUES (:name), (:email), (:password)");
				qSqlQuery.bindValue(":name", nickName);
				qSqlQuery.bindValue(":email", email);
				qSqlQuery.bindValue(":password", password);

				return qSqlQuery.exec() && qSqlQuery.next();
			}
		}
		database.close();
	}

    return 1;
}

bool DBManager::checkUserEmail(const QString &email) {
	if (database.open()) {
		if (!email.isEmpty()) {
			QSqlQuery qSqlQuery;
			qSqlQuery.prepare("SELECT id FROM users WHERE email = (:email)");
			qSqlQuery.bindValue(":email", email);

			database.close();
			return qSqlQuery.exec() && qSqlQuery.next();
		}
		database.close();
	}

    return false;
}

bool DBManager::checkUserNickName(const QString &nickName) {

	if (database.open()) {
		if (!nickName.isEmpty()) {
			QSqlQuery qSqlQuery;
			qSqlQuery.prepare("SELECT id FROM users WHERE name = (:nickname)");
			qSqlQuery.bindValue(":nickname", nickName);

			return qSqlQuery.exec() && qSqlQuery.next();
		}
		database.close();
	}

    return false;
}

bool DBManager::checkPassword(const QString &email, const QString &password) {
	if (database.open()) {
		if (!password.isEmpty()) {
			QSqlQuery qSqlQuery;
			qSqlQuery.prepare("SELECT password FROM users WHERE email = (:email)");
			qSqlQuery.bindValue(":email", email);

			if (qSqlQuery.exec() && qSqlQuery.next()) {
				qDebug() << qSqlQuery.record().value("password");
			}

			//qSqlQuery.
		}
		database.close();
	}
}

QJsonArray DBManager::getOnlineUsers() {
	QSqlQuery qSqlQuery("SELECT * FROM onlineUsers");

	if (database.open() && qSqlQuery.exec()) {
		QJsonArray users;

		while (qSqlQuery.next()) {
			int id = qSqlQuery.value("id").toInt();
			int userID = qSqlQuery.value("userID").toInt();
			int roomID = qSqlQuery.value("roomID").toInt();
			QJsonObject tempObject;
			tempObject.insert("id", id);
			tempObject.insert("userID", userID);
			tempObject.insert("roomID", roomID);
			users.push_back(tempObject);
		}
		return users;
	}

	return QJsonArray();
}


