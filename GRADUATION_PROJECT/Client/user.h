#ifndef USER_H
#define USER_H

#include "client.h"

#define DEPOSIT_OPERATION 1
#define WITHDRAWAL_OPERATION 2

class User : public Client
{
public:
    explicit User();
    // Abstract Class functions
    void GetAccNo(void);
    void ViewAccountBalance(void);
    void ViewTransactionHistory(void);
    void SendRequestToServer(void);
    bool Login(void);
    void start(void);
    // More functions for user mode
    void TransferAmount(void);
    void MakeTransaction(void);

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

#endif // USER_H
