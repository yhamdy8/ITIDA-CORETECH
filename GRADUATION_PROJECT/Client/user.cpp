#include "user.h"

#include <QDataStream>
#include <QDebug>


User::User() : cin(stdin),cout(stdout)
{
    m_role="user";
    connect(&socket,&QTcpSocket::connected,this,&User::connected);
    connect(&socket,&QTcpSocket::disconnected,this,&User::disconnected);
    connect(&socket,&QTcpSocket::stateChanged,this,&User::stateChanged);
    connect(&socket,&QTcpSocket::readyRead,this,&User::readyRead);
    connect(&socket,&QTcpSocket::errorOccurred,this,&User::error);
}


void User::TransferAmount(void)
{
    // Set Stream
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);

    QString AmountToSend,ToUserName,CancelBtn;
    do
    {
        // Send initial requests to the server
        m_request = "Transfer Amount";
        SendRequestToServer();
        // Take Data from the User
        cout << "Please Enter the Account UserName you want to Transfer to:" << Qt::endl;

        cout << "Transfer To UserName>> "; cout.flush();
        cin >> ToUserName;
        cout << "=======================================================" << Qt::endl;
        // Set first request to check if username is found
        m_request = "CHECK USER IS FOUND";
        // Send user name to server to check account is found
        outStream << m_request << ToUserName;
        // wait to send data to the server
        socket.waitForBytesWritten();
        // wait to receive data from the server
        socket.waitForReadyRead();
        cout << "=======================================================" << Qt::endl;
        // Case user isnot found
        if(m_ServerRespond.toBool() == false)
        {
            cout << "This UserName is not found,\n"
                    "Please Make sure you Enter the correct UserName" << Qt::endl;

            cout << "=======================================================" << Qt::endl;

            cout << "To Cancel operation press <" << CANCEL_OPERATION << ">\n"
                    "To Continue press any other key" << Qt::endl;

            cout << "Operation>> ";cout.flush();
            cin >> CancelBtn;
            if( CancelBtn.toInt() == CANCEL_OPERATION )
            {
                return;
            }
        }
    }while(m_ServerRespond.toBool() == false);
    // Send initial requests to the server
    m_request = "Transfer Amount";
    SendRequestToServer();
    cout << "=======================================================" << Qt::endl;
    // let the User set the amount
    cout << "Please specify the Amount to Transfer to " << ToUserName << Qt::endl;
    cout << "Amount EGP>> "; cout.flush();
    cin >> AmountToSend;
    // Send Second request to make the transfer from user account to the other account
    m_request = "Make The Transfer";
    // Send all data to the server
    outStream << m_request << ToUserName << AmountToSend << m_UserName;
    // wait to send to server
    socket.waitForBytesWritten();
    // wait till receiving the confermation from the server
    socket.waitForReadyRead();
    cout << "=======================================================" << Qt::endl;
    if(m_ServerRespond.toBool() == true)
    {
        cout << "Successful transfer from Account: " << m_UserName <<"\n"
                "To Account: " << ToUserName << "\n"
                "With the Amount of: " << AmountToSend << Qt::endl;
    }else{
        cout << "Trasnfer Error!\n Insufficient Balance" << Qt::endl;
    }
}

void User::MakeTransaction(void)
{
    // Set Stream
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);
    // Send initial requests to the server
    m_request = "Make Transaction";
    SendRequestToServer();

    // Send The user name to the server
    outStream << m_UserName;

    QString OperationToDo, TransActionAmount;
    // Take Operation from user
    do
    {
        // let user choose which operation to do
        cout << "=======================================================" << Qt::endl;
        cout << "Please Specify the Operation:\n"
                "For Deposit press <1>\n"
                "For Withdrawal press <2>\n"
                "To cancel press <3>" << Qt::endl;
        cout << "Operation>> "; cout.flush();
        cin >> OperationToDo;
        cout << "=======================================================" << Qt::endl;
        if( (OperationToDo.toInt() != DEPOSIT_OPERATION ) &&
            (OperationToDo.toInt() != WITHDRAWAL_OPERATION ) &&
            (OperationToDo.toInt() != EXIT_COMMAND )    )
        {
            cout << "Wrong Entery Please!" << Qt::endl;
        }
    }while((OperationToDo.toInt() != DEPOSIT_OPERATION ) &&
            (OperationToDo.toInt() != WITHDRAWAL_OPERATION ) &&
            (OperationToDo.toInt() != EXIT_COMMAND )    );
    // Set Operation
    switch(OperationToDo.toInt() )
    {
    case DEPOSIT_OPERATION:
        OperationToDo = "DEPOSIT";
        break;
    case WITHDRAWAL_OPERATION:
        OperationToDo = "WITHDRAWAL";
        break;
    case EXIT_COMMAND:
        return;
    default:
        qDebug() << "ERROR OCCURED WHILE TAKING TRANSACTION COMMANMD";
        return;
    }
    // take and Set amount of The TransAction
    cout << "Please Enter The Desired " << OperationToDo <<" Amount" <<Qt::endl;
    cout << OperationToDo << " Amount>> ";cout.flush();
    cin >> TransActionAmount;
    cout << "=======================================================" << Qt::endl;
    outStream << OperationToDo << TransActionAmount;
    // wait to send Data to server
    socket.waitForBytesWritten();
    // wait to receive the server respond
    socket.waitForReadyRead();
    cout << "=======================================================" << Qt::endl;
    bool TransactionDone = m_ServerRespond.toBool();
    if(TransactionDone)
    {
        cout << "Accepted Transaction" << Qt::endl;
    }else {
        cout << "Refused Transaction, Insufficient Amount" << Qt::endl;
    }
}

void User::ViewAccountBalance(void)
{
    // Send initial reqs
    m_request = "View Account Balance";
    SendRequestToServer();

    // Set DataSTream
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);

    outStream << m_UserName;
    // wait to send data to the stream
    socket.waitForBytesWritten();
    // Wait for server response
    socket.waitForReadyRead();

    cout << "Your Balance is: " << m_ServerRespond.toInt()
        <<  " EGP"<< Qt::endl;
}

void User::GetAccNo(void)
{
    // Send inital reqs
    m_request = "Get Account Number";
    SendRequestToServer();

    // Set DataSTream
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);
    // Send UserName to server to fetch his data
    outStream << m_UserName;
    // wait to send data to the stream
    socket.waitForBytesWritten();
    // Wait for server response
    socket.waitForReadyRead();
    // print the balance fetched from the server
    cout << "Your Account Number is: " << m_ServerRespond.toInt()
         << Qt::endl;
}

void User::ViewTransactionHistory(void)
{
    // Send initial reqs
    m_request = "View Transaction History";
    SendRequestToServer();
    cout << "=======================================================" << Qt::endl;
    // create a datastream to send the nedded info to the server to transfer the money.
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);

    QString CountToShow;
    // Let user set the count to show from the latest
    cout << "How many Trasaction to show from the history:" <<Qt::endl;
    cout << "Count To Show>> "; cout.flush();
    cin >> CountToShow;
    // Send the username and the count to the server
    outStream << m_UserName << CountToShow;
    // wait to send data to server
    socket.waitForBytesWritten();
    // wait to receive data from server
    socket.waitForReadyRead();
    cout << "=======================================================" << Qt::endl;
}

void User::SendRequestToServer(void)
{
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);
    outStream << m_request <<m_role;
}

void User::connectToHost(QString host, quint16 port)
{
    if(socket.isOpen()) disconnect();
    socket.connectToHost(host,port);
}

void User::disconnect()
{
    socket.close();
    socket.waitForDisconnected();
}

void User::connected()
{
    QTextStream input(stdin, QIODevice::ReadOnly);
    QString userInput = input.readLine().trimmed();
    socket.write(userInput.toUtf8());
}

void User::disconnected()
{
    qInfo()<<"Thank you!...system is closing";
    qInfo()<<"Disconnected";
}

void User::error(QAbstractSocket::SocketError socketerror)
{
    qInfo()<<"Error:"<<socketerror<<socket.errorString();
}

void User::stateChanged(QAbstractSocket::SocketState socketstate)
{
    QMetaEnum metaenum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    QString str= metaenum.valueToKey(socketstate);
}

bool User::Login(void)
{
    cout << "=======================================================" << Qt::endl;
    // Set Stream
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);
    // Set Request
    m_request = "Login";
    QString UserName, Password;
    // Send request type and User Mode to Server
    outStream << m_request << m_role;
    // Take User credentials to send to server
    cout << "Welcome to Banking Applications\n"
            "Login>> <UserName> <Password>" << Qt::endl;
    cout << "Login>> "; cout.flush();

    cin >> UserName >> Password;

    // Check for the right entery
    bool LoginOk =false;
    while(!LoginOk)
    {
        if(!( UserName.isEmpty() ) && !( Password.isEmpty() ) )
        {
            LoginOk = true;
        }else
        {
            cout << "Please enter valid Data" << Qt::endl;
        }
    }
    // Send Data to Server
    outStream << UserName << Password;
    LoginOk = false;
    // wait to send data
    socket.waitForBytesWritten();
    // wait for data received from server
    socket.waitForReadyRead();

    LoginOk = m_ServerRespond.toBool();
    if(LoginOk)
    {
        m_UserName = UserName;
    }else {
        cout << "Wrong Credentials" << Qt::endl;
    }
    // cout << "=======================================================" << Qt::endl;
    return LoginOk;
}

void User::readyRead()
{
    QDataStream inStream(&socket);
    inStream.setVersion(QDataStream::Qt_6_6);
    bool Response = false;
    if( m_request == "Login")
    {
        // QString UserName;
        // Receive from the Data from the Socket Stream
        inStream >> Response;
        // Set Values of login return
        m_ServerRespond.setValue(Response);
        // m_UserName = UserName;
    }else
        if (m_request=="View Account Balance")
        {
            QString AccountMoney;
            //take the money in the account from the server and save it in the server respond
            inStream >> AccountMoney;
            m_ServerRespond.setValue(AccountMoney);
        }else
            if(m_request=="Get Account Number")
            {
                QString AccNum;
                //know if the transaction succeed or not from the server and save it in the server respond
                inStream>>AccNum;
                m_ServerRespond.setValue(AccNum);
            } else
            if(m_request == "Make Transaction")
            {
                inStream >> Response;
                m_ServerRespond.setValue(Response);
            }else
                if(m_request == "View Transaction History")
            {
                QString History;
                // read response from server
                inStream >> Response >> History;
                if(Response == true)
                {
                    cout << "Transaction History is\n"
                         << History << Qt::endl;
                }else
                {
                    cout << "No Trasaction Found in account" << Qt::endl;
                }
            } else
                if( m_request == "CHECK USER IS FOUND")
            {
                //read response from the server
                inStream >> Response;
                m_ServerRespond.setValue(Response);
            }else
                if(m_request == "Make The Transfer")
            {
                // Take Response from the server
                inStream >> Response;
                m_ServerRespond.setValue(Response);
            }
}

void User::start(void)
{
    QString CommandToExcute,LoopAgain;
    while(true)
    {
        cout << "=======================================================" << Qt::endl;
            // let User choose what to do
        cout <<
            "Choose from the list: \n1-View Account Balance\n2-View Transaction History\n"
            "3-Get Account Number\n4-Transfer Amount\n"
            "5-MakeTransaction\n"
            "6-Exit Application"
             << Qt::endl;
        cout << "=======================================================" << Qt::endl;
        cout << "Command ID >> "; cout.flush();
        cin >> CommandToExcute;
        cout << "=======================================================" << Qt::endl;
        switch(CommandToExcute.toInt())
        {
        case 1:
            ViewAccountBalance();
            break;
        case 2:
            ViewTransactionHistory();
            break;
        case 3:
            GetAccNo();
            break;
        case 4:
            TransferAmount();
            break;
        case 5:
            MakeTransaction();
            break;
        case 6:
            cout << "Thank you for using the bank application!!" << Qt::endl;
            cout << "=======================================================" << Qt::endl;
            exit(0);
        default:
            cout << "Wrong Entery Please Choose again!" << Qt::endl;
            break;
        }
        cout << "=======================================================" << Qt::endl;
        // Let the user choose either to do more requests or to exit the program
        cout << "For another request Press <" << TO_CONTINUE << ">\n"
             << "Enter Any other key to exit: " <<Qt::endl;
        cout << "Another Request >> "; cout.flush();
        cin >> CommandToExcute ;
        if( !(CommandToExcute.toInt() == TO_CONTINUE) )
        {
            cout << "Thank you for using the bank application!!" << Qt::endl;
            cout << "=======================================================" << Qt::endl;
            exit(0);
        }
        cout << "=======================================================" << Qt::endl;
    }
}



