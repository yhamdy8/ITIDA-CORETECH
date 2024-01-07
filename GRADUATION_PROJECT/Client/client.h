#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QMetaEnum>
#include <QTextStream>

// For Code Readability
#define ADMIN_USER 1
#define STANDARD_USER 2
#define EXIT_COMMAND 3
#define TO_CONTINUE 1
#define CANCEL_OPERATION 1


class Client : public QObject
{
    Q_OBJECT
public:
   explicit Client(QObject *parent = nullptr);
   virtual void GetAccNo(void)=0;
   virtual void ViewAccountBalance(void)=0;
   virtual void ViewTransactionHistory(void)=0;
   virtual void SendRequestToServer(void)=0;
   virtual bool Login(void)=0;
   virtual void start(void)=0;
 protected:
    QString m_role;
    QString m_request;
    QVariant m_ServerRespond;
    QString m_AccountNumber;
    QString m_UserName;
    QString m_Balance;
};

#endif // CLIENT_H
