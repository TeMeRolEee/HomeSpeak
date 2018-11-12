#pragma once

#include <QtSql>
#include <QtCore/QString>
#include <QtSql/QSqlDatabase>

class DBManager {
public:
    DBManager(const QString &path);

    bool initDataBase();

    bool addUser(const QVector<QString> &data);

    bool checkUserIDExists(const QString &id);

    bool checkUserEmail(const QString &email);

    bool checkUserNickName(const QString &nickName);

    int getUsersRoomId(const int &id);

    int registerUser(const QString &email, const QString &password, const QString &nickName);

private:
    QString dataBaseFilePath;
    QSqlDatabase qSqlDatabase;
};


