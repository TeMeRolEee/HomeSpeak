#pragma once

#include <QtSql>
#include <QtCore/QString>
#include <QtSql/QSqlDatabase>

class DBManager {
public:
    DBManager(const QString &path);

    bool initDataBase();

    bool checkUserIDExists(const QString &id);

    bool checkUserEmail(const QString &email);

    bool checkUserNickName(const QString &nickName);

    bool checkPassword(const QString &email, const QString &password);

    int getUsersRoomId(const int &id);

    int registerUser(const QString &email, const QString &password, const QString &nickName);

    QJsonArray getOnlineUsers();

private:
    QString dataBaseFilePath;
    QSqlDatabase database;
};


