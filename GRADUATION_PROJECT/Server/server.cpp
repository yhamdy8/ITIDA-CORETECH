#include "server.h"
#include "JsonHandler.h"
#include <QDebug>
#include <QThread>
Server::Server(QObject *parent)
    : QObject{parent}
{
    connect(&server,&QTcpServer::newConnection,this,&Server::newConnection);
}

void Server::start()
{
    if(!server.listen(QHostAddress::Any,1234))
    {
        qWarning()<<server.errorString();
        return;
    }
    qInfo()<<"Listening..";
}

void Server::quit()
{
    server.close();
}

void Server::newConnection()
{
    QTcpSocket* socket = server.nextPendingConnection();
    connect(socket,&QTcpSocket::disconnected,this,&Server::disconnected);
    connect(socket,&QTcpSocket::readyRead,this,&Server::readyRead);
    qInfo()<<"connected to"<<socket;

}

void Server::disconnected()
{
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    qInfo() << "Disconnected" << socket;
    qInfo() << " From parent" << socket->parent();
}

void Server::readyRead()
{
    //create pointer to the socket connected to the object send the request
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    //create an in datasream to take the needed data from the client
    QDataStream inStream(socket);
    inStream.setVersion(QDataStream::Qt_6_6);
    //take the request message and the role of our client to be able to handle the request
    QString FirstReq,UserMode ;
    inStream >> FirstReq >> UserMode;

    //call this method to handle the request according to client role
    Handlerequest(FirstReq,UserMode);
}

void Server::Handlerequest(QString request,QString role)
{
    //create pointer to the socket connected to the object send the request
    QTcpSocket* socket=qobject_cast<QTcpSocket*>(sender());
    //create an in datasream to take the needed data from the client
    QDataStream inStream(socket);
    inStream.setVersion(QDataStream::Qt_6_6);
    //create an out datastream to send the respond to the client
    QDataStream outStream(socket);
    outStream.setVersion(QDataStream::Qt_6_6);

    //Define json files directory
    // QString Path(DB_DIRECTORY);
    //Define json files name
    QString AdminFile = QString(DB_DIRECTORY) + QString(ADMIN_FILE_NAME);
    QString StandardFile = QString(DB_DIRECTORY) + QString(STANDARD_FILE_NAME);


    //check if oour client is user or admin to handle his request
    if(role.toUpper()=="USER")
    {
        if(request == "Login")
        {
            bool ok = true;
            QString UserName,Password;
            // Read variables from the stream
            inStream >> UserName >> Password;
            qInfo() << "Received from client:\nUserName " << UserName<<" \nPassword "<<Password ;
            //sending respond to the server using the socket
            ok = JsonHandler::CheckLogin(StandardFile, UserName,Password);
            qInfo() << "ok is " << ok;
            outStream<<ok;
        }else
            if(request=="Transfer Amount")
            {
                QString SecondReq,ToUserName;
                    // read data from the client
                inStream >> SecondReq;
                if(SecondReq == "CHECK USER IS FOUND")
                {
                    // Read user name from the stream
                    inStream >> ToUserName;
                    bool found = JsonHandler::CheckUserFound(StandardFile,ToUserName);
                    // Send if user is found back to the client
                    outStream << found;
                }else
                    if(SecondReq == "Make The Transfer")
                {
                    QString AmountToTransfer, FromUserName, FrmUsrNameCrntBalance;
                    bool ok = false;
                    QString Field = "Balance";
                    // Read Data from the client
                    inStream >> ToUserName >> AmountToTransfer >> FromUserName;
                    // qInfo() << "Recvv>>>>>" << ToUserName << AmountToTransfer << FromUserName;
                    // Get FromUser current balance
                    ok = JsonHandler::GetField(StandardFile,FromUserName,Field,FrmUsrNameCrntBalance);
                    if(ok)
                    {
                        // Check he has sufficient Amount to make the transfer
                        if( (FrmUsrNameCrntBalance.toInt() - AmountToTransfer.toInt() ) >= 0)
                        {
                            // Set FromUser new balance
                            QString FromUsrNewBalance = QString::number( FrmUsrNameCrntBalance.toInt() - AmountToTransfer.toInt() );
                            ok = JsonHandler::SetField(StandardFile,FromUserName,Field,FromUsrNewBalance);
                            // Save transaction history
                            QString FromUsrTrans = "-" + AmountToTransfer;
                            JsonHandler::SetTransactionHistory(StandardFile,FromUserName,FromUsrTrans);
                            if(ok)
                            {
                                // Get ToUser current bala
                                QString ToUserNameCrntBalance;
                                ok = JsonHandler::GetField(StandardFile,ToUserName,Field,ToUserNameCrntBalance);
                                if(ok)
                                {
                                    // Set ToUsr new balance
                                    QString ToUsrNewBalance = QString::number( ToUserNameCrntBalance.toInt() + AmountToTransfer.toInt() );
                                    ok = JsonHandler::SetField(StandardFile,ToUserName,Field,ToUsrNewBalance);
                                    // Save transaction history
                                    QString ToUsrTrans = "+" + AmountToTransfer;
                                    JsonHandler::SetTransactionHistory(StandardFile,ToUserName,ToUsrTrans);
                                }
                            } 
                        }else{
                            //Insuff Amount found
                            ok = false;
                        }
                    }
                    // Send if ok or not to the client
                    outStream << ok;
                }
            }
            else
                if( request == "View Account Balance")
            {
                QString UserName, BalanceValue;
                QString Field = "Balance";
                inStream >> UserName;
                JsonHandler::GetField(StandardFile, UserName, Field, BalanceValue);
                // Send value to the client on the socket
                outStream << BalanceValue;
            }
            else
                if( request == "Get Account Number")
            {
                QString UserName, AccNum;
                QString Field = "Account Number";
                inStream >> UserName;
                JsonHandler::GetField(StandardFile, UserName, Field, AccNum);
                // Send value to the client on the socket
                outStream << AccNum;
            }else
                if( request == "Make Transaction" )
            {
                bool ok = false;
                QString OperationToDo,TransactionAmount, UserName, AccountBalance;
                QString BalanceField = "Balance";
                // Read the operation and the amount from the stream
                inStream >> UserName >> OperationToDo >> TransactionAmount;
                // Get the user's current balance
                JsonHandler::GetField(StandardFile,UserName,BalanceField,AccountBalance);
                if( OperationToDo.toUpper() == "DEPOSIT" )
                {
                    // Add the transaction amount to the current balance
                    qint32 NewBalance = AccountBalance.toInt() + TransactionAmount.toInt();
                    QString UpdatedBalance = QString::number(NewBalance);
                    // Set user's balance with the new Balance
                    ok = JsonHandler::SetField(StandardFile,UserName,BalanceField, UpdatedBalance);
                    qInfo() << "Transaction value added to balance bool >> " << ok;
                    // save transaction history
                    QString Transaction = "+" +TransactionAmount;
                    ok = JsonHandler::SetTransactionHistory(StandardFile,UserName,Transaction);
                    qInfo() << "Transaction History saved bool >> " << ok;
                }else
                    if( OperationToDo.toUpper() == "WITHDRAWAL" )
                {
                    // Make sure that user balance is sufficient to withdraw
                    if( (AccountBalance.toInt() - TransactionAmount.toInt() ) >= 0 )
                    {
                        // Subtract the transaction amount from the user's current balance
                        qint32 NewBalance = AccountBalance.toInt() - TransactionAmount.toInt();
                        QString UpdatedBalance = QString::number(NewBalance);
                        // Set the user's balance with the new balance
                        ok = JsonHandler::SetField(StandardFile,UserName,BalanceField, UpdatedBalance);
                        qInfo() << "Transaction value added to balance bool >> " << ok;
                        //save transaction history
                        QString Transaction = "-" +TransactionAmount;
                        ok = JsonHandler::SetTransactionHistory(StandardFile,UserName,Transaction);
                        qInfo() << "Transaction History saved bool >> " << ok;
                    } else {
                        qDebug() << "Insufficient Amount";
                        ok = false;
                    }
                }
                // Send Respond back to client if done or not and the new value
                outStream << ok;
            } else
                if( request == "View Transaction History" )
            {
                QString UserName,Count,History;
                bool ok = false;
                // Read the data from the stream
                inStream >> UserName >> Count;
                qInfo() << "Data received is >>>" << UserName << Count;
                ok = JsonHandler::GetTransactionHistory(StandardFile,UserName,Count,History);
                qDebug() << "ok is >> " << ok<< " History is:\n" << History;
                // Send respond to Client
                outStream << ok << History;
            }
    }else if(role.toUpper()=="ADMIN")
    {
        if(request=="Login")
        {
            bool ok = true;
            QString UserName,Password;
            // Read variables from the stream
            inStream >> UserName >> Password;
            qInfo() << "Received from client:\nUserName " << UserName<<" \nPassword "<<Password ;
            //sending respond to the server using the socket
            ok = JsonHandler::CheckLogin(AdminFile, UserName,Password);
            qInfo() << "ok is " << ok;
            outStream<<ok;
        }else
            if(request == "Get Account Number")
        {
            QString UserName,UserMode, AccountNum;
            QString Field = "Account Number";
            bool ok = false;
            inStream >> UserMode >> UserName;
            qInfo() << "Received from client:\nUserMode "<< UserMode
                    << "\nUserName "<< UserName;
            if(UserMode.toUpper() == "ADMIN")
            {
                ok = JsonHandler::GetField(AdminFile, UserName, Field, AccountNum);
            }else
                if(UserMode.toUpper() == "STANDARD")
            {
                ok = JsonHandler::GetField(StandardFile, UserName, Field, AccountNum);
            }
            outStream << ok << AccountNum;
            qInfo() << "Acc num = " << AccountNum;
        }else
            if(request == "View Account Balance")
        {
            QString UserName, AccBalance;
            QString Field = "Balance";
            bool ok = false;

            inStream >> UserName;
            // access data base and check for user and their balance
            ok = JsonHandler::GetField(StandardFile, UserName, Field, AccBalance);

            qInfo() << "Received from client:" << UserName;

            outStream << ok << AccBalance;
            // qInfo() << "Acc balance" << AccBalance;
        }else
            if(request == "View Data Base")
        {
            QString DBType,JsonDB;
            bool ok = false;
            //Read Dataype from stream
            inStream >> DBType;
            //Take database from json and set it into the variable
            if(DBType.toUpper() == "ADMIN")
            {
                ok = JsonHandler::PrintDataBase(AdminFile,JsonDB);
            }else if(DBType.toUpper() == "STANDARD")
            {
                ok = JsonHandler::PrintDataBase(StandardFile,JsonDB);
            }
            outStream << ok << JsonDB;
            qInfo() << "Data Base sent to user " << ok
                    << " data base \n" << JsonDB;
        }else
            if(request == "Create New User")////////////
        {   qInfo() << "SECOND REQ RECEIVED";
            QString SecondaryReq, UserMode,UserName;
            // Read Secondary Request from the stream
            inStream >> SecondaryReq;
            if(SecondaryReq == "CHECK USER IS FOUND")
            {
                bool Found = false;
                // Read rest of the data from the stream
                inStream >> UserMode >> UserName;
                qInfo() << "Data rec>>>>>><<<><><>>>" << UserMode << UserName;
                // Search in the json file
                if(UserMode.toUpper() == "ADMIN")
                {
                    Found = JsonHandler::CheckUserFound(AdminFile,UserName);
                }else
                    if(UserMode.toUpper() == "STANDARD")
                {
                    Found = JsonHandler::CheckUserFound(StandardFile,UserName);
                }else{
                    qDebug() << "Error specifying User Mode";
                    Found = false;
                }
                // Send to client if the userName is found or not
                outStream << Found;
                qInfo() << "found or not bool >>>>" << Found;
            }else
            if(SecondaryReq == "Create Now")
            {
                bool ok = false;
                QString NewUserPass,NewUserAge,NewUserFullName;
                // Read data from the stream
                inStream >> UserMode >> UserName >> NewUserPass
                         >> NewUserFullName >> NewUserAge;
                QVariantMap NewUser;
                NewUser["Age"] = NewUserAge;
                NewUser["Password"] = NewUserPass;
                NewUser["Full Name"] = NewUserFullName;
                if(UserMode.toUpper() == "ADMIN")
                {
                    NewUser["Account Number"] = JsonHandler::AccountNumberGenerator(UserName);
                    ok = JsonHandler::CreateNewUser(AdminFile,UserName,NewUser);
                }else
                    if(UserMode.toUpper() == "STANDARD" )
                {
                    QString NewUserBalance;
                    // Read balance data from the stream
                    inStream >> NewUserBalance;
                    NewUser["Account Number"] = JsonHandler::AccountNumberGenerator(UserName);
                    NewUser["Balance"] = NewUserBalance;
                    ok = JsonHandler::CreateNewUser(StandardFile,UserName,NewUser);
                }
            // Return Status to the client
                outStream << ok;
            }
        }else
            if(request  == "Delete User")
        {
            // variable to carry username required to delete
            QString UserName, UserMode;
            bool deleted = false;
            //Read from the stream
            inStream >> UserMode >> UserName;
            qInfo() << UserMode << UserName;
            // Goto json file and delete the
            if(UserMode.toUpper() == "ADMIN")
            {
                deleted = JsonHandler::DeleteUser(AdminFile,UserName);
            }else if(UserMode.toUpper() == "STANDARD")
            {
                deleted = JsonHandler::DeleteUser(StandardFile,UserName);
            }
            outStream << deleted;
        }else
            if(request == "Get Trans History")
        {
            QString UserName,Count,Data;
            bool ok;
            // Receive data from the client
            inStream >> UserName >> Count;
            ok = JsonHandler::CheckUserFound(StandardFile,UserName);
            if(ok)
            {
                ok = JsonHandler::GetTransactionHistory(StandardFile,UserName,Count,Data);
                if(!ok)
                {
                    Data = "No Transaction Found to this user";
                }
            }else
            {
                //userName not found
                Data = "UserName Not Found in Database";
            }
            //Send data back to the Client
            outStream << ok << Data;
        }else
            if(request == "Update User")
        {
            QString SecondReq, UserName, UserMode;
            // Read from the server
            inStream >> SecondReq;
            if(SecondReq == "CHECK USER IS FOUND")
            {
                bool Found = false;
                // Read UserMode & UserName to check on them
                inStream >> UserMode >> UserName;
                if(UserMode.toUpper() == "ADMIN")
                {
                    Found = JsonHandler::CheckUserFound(AdminFile,UserName);
                }else if(UserMode.toUpper() == "STANDARD")
                {
                    Found = JsonHandler::CheckUserFound(StandardFile,UserName);
                }else{
                    qDebug() << "Unkown User Mode";
                    Found = false;
                }
                // Send response to the client as it's found or not
                outStream << Found;
            }else
                if(SecondReq == "Make The Update")
            {
                QString FieldToUpdate,NewFieldValue;
                bool ok = false;
                // Read Data from the socket
                inStream >> UserMode >> UserName >> FieldToUpdate >> NewFieldValue;
                if(UserMode.toUpper() == "ADMIN")
                {
                    ok = JsonHandler::SetField(AdminFile,UserName,FieldToUpdate,NewFieldValue);
                }else if(UserMode.toUpper() == "STANDARD")
                {
                    ok = JsonHandler::SetField(StandardFile,UserName,FieldToUpdate,NewFieldValue);
                }else{
                    qDebug() << "Unkown User Mode";
                    ok = false;
                }
                // Send Response back to the client if its updated or not
                outStream << ok;
            }else {
                qDebug() << "Unkown Secondary Request!";
                outStream << false;
            }
        }
    }
}




