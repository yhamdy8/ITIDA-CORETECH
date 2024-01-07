#ifndef ADMIN_H
#define ADMIN_H

#include "client.h"

// For Code Readability
#define FULL_NAME_FIELD 1
#define PASSWORD_FIELD 2
#define AGE_FIELD   3
#define BALANCE_FIELD 4


class Admin : public Client
{
public:
    explicit Admin();
    // Functions from Abstract Class
    void GetAccNo(void);
    void ViewAccountBalance(void);
    void SendRequestToServer(void);
    bool Login(void);
    void start(void);
    void ViewTransactionHistory(void);
    // more functions for the admin user
    void ViewBankDatabase(void);
    void CreateNewUser(void);
    void DeleteUser(void);
    void UpdateUser(void);
    void SearchUserName(const QString UserMode, const QString UserName);
signals:
public slots:
    void connectToHost(QString host,quint16 port);
    void disconnect();
protected slots:
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError socketerror);
    void stateChanged(QAbstractSocket::SocketState socketstate);
    void readyRead();
private:
        QTcpSocket socket;
        QTextStream cin;
        QTextStream cout;

};

#endif // ADMIN_H
