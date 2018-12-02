#include <QtSql/QSqlQuery>
#include <QtCore/QVector>
#include "dbmanager.h"

DBManager::DBManager(const QString &path) : dataBaseFilePath(path) {
}

bool DBManager::initDataBase() {
    qSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    qSqlDatabase.setDatabaseName(dataBaseFilePath);
	QSqlQuery createUsersTableQuery;
	QString usersTableQueryText = "CREATE TABLE `users` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, `name` TEXT NOT NULL, `email` TEXT NOT NULL UNIQUE, `password` TEXT NOT NULL UNIQUE )";

	QSqlQuery createOnlineUsersQuery;
	QString onlineTableQueryText = "CREATE TABLE `onlineUsers` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `userID` INTEGER NOT NULL UNIQUE, `roomID` INTEGER NOT NULL )";

	QSqlQuery createRoomsUsersQuery;
	QString roomsTableQueryText = "CREATE TABLE `rooms` ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, `roomName` TEXT NOT NULL )";

	return qSqlDatabase.open() &&
			createUsersTableQuery.exec(usersTableQueryText) &&
			createOnlineUsersQuery.exec(onlineTableQueryText) &&
			createRoomsUsersQuery.exec(roomsTableQueryText);
}

bool DBManager::checkUserIDExists(const QString &id) {
    if (!id.isEmpty()) {
        QSqlQuery qSqlQuery;
        qSqlQuery.prepare("SELECT id FROM users WHERE id = (:id)");
        qSqlQuery.bindValue(":id", id);

        return qSqlQuery.exec() && qSqlQuery.next();
    }

    return false;
}

int DBManager::getUsersRoomId(const int &id) {
    //TODO FINISH UP THIS FUNCTION!
    if (id >= 0) {
        QSqlQuery qSqlQuery;
        qSqlQuery.prepare("SELECT roomID FROM ");

        return 0;
    }
}

int DBManager::registerUser(const QString &email, const QString &password, const QString &nickName) {
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

    return 1;
}

bool DBManager::checkUserEmail(const QString &email) {
    if (!email.isEmpty()) {
        QSqlQuery qSqlQuery;
        qSqlQuery.prepare("SELECT id FROM users WHERE email = (:email)");
        qSqlQuery.bindValue(":email", email);

        return qSqlQuery.exec() && qSqlQuery.next();
    }

    return false;
}

bool DBManager::checkUserNickName(const QString &nickName) {
    if (!nickName.isEmpty()) {
        QSqlQuery qSqlQuery;
        qSqlQuery.prepare("SELECT id FROM users WHERE name = (:nickname)");
        qSqlQuery.bindValue(":nickname", nickName);

        return qSqlQuery.exec() && qSqlQuery.next();
    }

    return false;
}

bool DBManager::checkPassword(const QString &email, const QString &password) {
    if (!password.isEmpty()) {
        QSqlQuery qSqlQuery;
        qSqlQuery.prepare("SELECT password FROM users WHERE email = (:email)");
        qSqlQuery.bindValue(":email", email);

        if (qSqlQuery.exec() && qSqlQuery.next()) {
            qDebug() << qSqlQuery.record().value("password");
        }

        //qSqlQuery.
    }


}
