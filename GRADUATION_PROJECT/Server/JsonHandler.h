#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>

/*
 * Configurations to the json file
 *
 */
#define DB_DIRECTORY "E:/qt/Final/DataBase/"
#define STANDARD_FILE_NAME "StandardUser.json"
#define ADMIN_FILE_NAME "AdminUser.json"


class JsonHandler
{
    //Q_OBJECT
public:
    JsonHandler();
    static bool CheckUserFound(const QString &fileName, const QString &UserName);
    static bool CheckLogin(const QString &fileName, const QString &UserName, const QString &UsrPassword);
    static bool GetField(const QString &fileName, const QString &UserName, const QString &Field, QString &FieldValue);
    static bool SetField(const QString &fileName, const QString &UserName, const QString &Field, const QString &NewValue);
    static bool PrintDataBase(const QString &fileName, QString &JsonDataBase);
    static bool DeleteUser(const QString &fileName, const QString &UserName);
    static bool SetTransactionHistory(const QString &filename, const QString &UserName, const QString &Transaction);
    static bool GetTransactionHistory(const QString &filename, const QString &UserName, const QString Count, QString &HistoryData);
    static bool CreateNewUser(const QString &fileName, const QString &NewUserName, const QVariantMap &UserData);
    static QString AccountNumberGenerator(const QString& UserName);
private:
    static QMutex mutex;
};

#endif // JSONHANDLER_H
