#include <QtSql/QSqlQuery>
#include <QtCore/QVector>
#include "dbmanager.h"

DBManager::DBManager(const QString &path) : dataBaseFilePath(path) {
}

bool DBManager::initDataBase() {
    qSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    qSqlDatabase.setDatabaseName(dataBaseFilePath);

    return qSqlDatabase.open();
}

bool DBManager::addUser(const QVector<QString> &data) {

    QSqlQuery qSqlQuery;
    qSqlQuery.prepare("INSERT INTO users id VALUES (:id)");
    qSqlQuery.bindValue(":id", data.at(0));

    return qSqlQuery.exec() && qSqlQuery.next();
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
