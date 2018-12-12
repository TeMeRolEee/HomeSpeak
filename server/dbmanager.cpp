#include <QtSql/QSqlQuery>
#include <QtCore/QVector>
#include "dbmanager.h"

DBManager::DBManager(const QString &path) : dataBaseFilePath(path) {
}

bool DBManager::initDataBase() {
    database = QSqlDatabase::addDatabase("QSQLITE");

    database.setDatabaseName(dataBaseFilePath);



	if (database.open()) {
        QSqlQuery createUsersTableQuery("CREATE TABLE IF NOT EXISTS `users` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, `name` TEXT NOT NULL, `email` TEXT NOT NULL UNIQUE, `password` TEXT NOT NULL UNIQUE )");

        QSqlQuery createOnlineUsersQuery("CREATE TABLE IF NOT EXISTS `onlineUsers` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `userID` INTEGER NOT NULL UNIQUE, `roomID` INTEGER NOT NULL )");

        QSqlQuery createRoomsUsersQuery("CREATE TABLE IF NOT EXISTS `rooms` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `roomName` TEXT NOT NULL )");

        if (createUsersTableQuery.exec()
            && createOnlineUsersQuery.exec()
            && createRoomsUsersQuery.exec()) {
                database.close();
                qDebug() << "megy";
                return true;
        } else {
            database.close();
            return true;
        }
	} else {
        QTextStream output(stdout);
        output << QStringLiteral("Couldn't connect to database");
        output.flush();

        return false;
    }
}

bool DBManager::checkUserIDExists(const QString &id) {
	if (database.open()) {
		if (!id.isEmpty()) {
			QSqlQuery qSqlQuery;
			qSqlQuery.prepare("SELECT id FROM users WHERE id = (:id)");
			qSqlQuery.bindValue(":id", id);

			bool res = qSqlQuery.exec() && qSqlQuery.next();
			database.close();
			return res;
		}

		database.close();
	}
    return false;
}

int DBManager::getUsersRoomId(const int &id) {

	if (database.open()) {
		if (id >= 0) {
			QSqlQuery qSqlQuery;
			qSqlQuery.prepare("SELECT roomID FROM onlineUsers WHERE userID = (:id)");
            qSqlQuery.bindValue(":id", id);

            int res = -1;

            if (qSqlQuery.exec() && qSqlQuery.next()) {
                res = qSqlQuery.value(qSqlQuery.record().indexOf("roomID")).toInt();
            }

            database.close();
            return res;
		}

		database.close();
	}

	return -1;
}

int DBManager::registerUser(const QString &email, const QString &password, const QString &nickName) {
	if (database.open()) {
	    qDebug() << "registering";
		if (!email.isEmpty() && !password.isEmpty() && !nickName.isEmpty()) {
			if (!checkUserEmail(email) && checkUserNickName(nickName)) {
				QSqlQuery qSqlQuery;
                qDebug() << "valmigmdalddlkgndf";
                database.open();
				qSqlQuery.prepare("INSERT INTO users (name, email, password) VALUES ((:name), (:email), (:password))");
				qSqlQuery.bindValue(":name", nickName);
				qSqlQuery.bindValue(":email", email);
				qSqlQuery.bindValue(":password", password);

                int res = qSqlQuery.exec() && qSqlQuery.next();
                qDebug() << "registerin23esadasdsafasfg";
                database.close();
                return res;
			}
		}
		database.close();
	}

    return 1;
}

bool DBManager::checkUserEmail(const QString &email) {
	//if (database.open()) {
		if (!email.isEmpty()) {
			QSqlQuery qSqlQuery;
			qSqlQuery.prepare("SELECT id FROM users WHERE email = (:email)");
			qSqlQuery.bindValue(":email", email);

            bool res = qSqlQuery.exec() && qSqlQuery.next();
            //database.close();
            return res;
		}
		//database.close();
	//}

    return false;
}

bool DBManager::checkUserNickName(const QString &nickName) {

	//if (database.open()) {
		if (!nickName.isEmpty()) {
			QSqlQuery qSqlQuery;
			qSqlQuery.prepare("SELECT id FROM users WHERE name = (:nickname)");
			qSqlQuery.bindValue(":nickname", nickName);

            bool res = qSqlQuery.exec() && qSqlQuery.next();
            //database.close();
            return res;
		}
		//database.close();
	//}

    return false;
}

bool DBManager::checkPassword(const QString &email, const QString &password) {
    bool passwordOK = false;

	if (database.open()) {
        if (!password.isEmpty()) {
            QSqlQuery qSqlQuery;
            qSqlQuery.prepare("SELECT password FROM users WHERE email = (:email)");
            qSqlQuery.bindValue(":email", email);

            if (qSqlQuery.exec() && qSqlQuery.next()) {
                if (qSqlQuery.value(qSqlQuery.record().indexOf("password")).toString() == password) {
                    passwordOK =  true;
                }
            }
        }

		database.close();
	}

	return passwordOK;
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

		database.close();
		return users;
	}

	return QJsonArray();
}

int DBManager::getUserID(const QString &email) {
	QSqlQuery qSqlQuery;
	qSqlQuery.prepare("SELECT password FROM users WHERE email = (:email)");
	qSqlQuery.bindValue(":email", email);

	if (database.open() && qSqlQuery.exec()) {
		int id = qSqlQuery.value("id").toInt();
		database.close();
		return id;
	}

	return -1;
}

bool DBManager::addToOnlineUsers(int userID, int roomID) {
	if (database.open()) {
		if (userID >= 0) {
			QSqlQuery qSqlQuery;

			qSqlQuery.prepare("INSERT INTO onlineUsers (userID, roomID) VALUES ((:userID), (:roomID))");
			qSqlQuery.bindValue(":userID", userID);
			qSqlQuery.bindValue(":roomID", roomID);

			bool execValue = qSqlQuery.exec() && qSqlQuery.next();
			database.close();
			return execValue;
		}
		database.close();
	}
	return false;
}

bool DBManager::removeFromOnlineUsers(int userID, int roomID) {
    if (database.open()) {
        if (userID >= 0) {
            QSqlQuery qSqlQuery;

            qSqlQuery.prepare("DELETE FROM onlineUsers (userID, roomID) VALUES ((:userID), (:roomID))");
            qSqlQuery.bindValue(":userID", userID);
            qSqlQuery.bindValue(":roomID", roomID);

            bool execValue = qSqlQuery.exec() && qSqlQuery.next();
            database.close();
            return execValue;
        }
        database.close();
    }
    return false;
}


