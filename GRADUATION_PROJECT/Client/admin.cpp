#include "admin.h"

#include <QTextStream>
#include <QCoreApplication>



Admin::Admin() : cin(stdin),cout(stdout)
{

    m_role="admin";
    connect(&socket,&QTcpSocket::connected,this,&Admin::connected);
    connect(&socket,&QTcpSocket::disconnected,this,&Admin::disconnected);
    connect(&socket,&QTcpSocket::stateChanged,this,&Admin::stateChanged);
    connect(&socket,&QTcpSocket::readyRead,this,&Admin::readyRead);
    connect(&socket,&QTcpSocket::errorOccurred,this,&Admin::error);
}

void Admin::ViewAccountBalance(void)
{
    // Send initial request to the server
    m_request = "View Account Balance";
    SendRequestToServer();
    cout << "=======================================================" << Qt::endl;
    // create a datastream to send the nedded info to the server to transfer the money.
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);
    // take from user the mode and username
    QString UserName;

    cout << "Enter Username to show Account Balance:" << Qt::endl;
    cout << "UserName>> "; cout.flush();
    cin >> UserName;
    cout << "=======================================================" << Qt::endl;
    outStream << UserName;
    // wait to send data to server
    socket.waitForBytesWritten();
    //wait for the respond from the server to view it to the client
    socket.waitForReadyRead();
    bool isFound = m_ServerRespond.toBool();
    if(isFound)
    {
        cout << "Account Balance is : " << m_Balance << Qt::endl;
    }else
    {
        cout << "Wrong Account UserName!" << Qt::endl;;
    }
}

void Admin::GetAccNo(void)
{
    // Send Initial requests to server
    m_request = "Get Account Number";
    SendRequestToServer();
    cout << "=======================================================" << Qt::endl;
    // create a datastream to send the nedded info to the server to transfer the money.
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);
    // take from user the mode and username
    QString UserName, UserMode;
    cout << "Please specify User Mode:\n"
            "For admin Mode press <" << ADMIN_USER << ">\n"
            "For Standard Mode press <" << STANDARD_USER << ">" << Qt::endl;
    cout << "UserMode>> "; cout.flush();
    cin >> UserMode;
    if( (UserMode.toInt() == ADMIN_USER) )
    {
        UserMode = "ADMIN";
    }else if( (UserMode.toInt() == STANDARD_USER) )
    {
        UserMode = "STANDARD";
    }else {
        cout << "Wrong Entery" << Qt::endl;
        return;
    }
    cout << "=======================================================" << Qt::endl;
    cout << "Enter Username to show Account Number:" << Qt::endl;
    cout << "UserName>> "; cout.flush();
    cin >> UserName;

    outStream << UserMode << UserName;

    socket.waitForBytesWritten();
    //wait for the respond from the server to view it to the client
    socket.waitForReadyRead();

    bool isFound = m_ServerRespond.toBool();
    if(isFound)
    {
        cout <<"Account number is :" << m_AccountNumber << Qt::endl;
    }else
    {
       cout << "Account Not Found" << Qt::endl;
    }
    cout << "=======================================================" << Qt::endl;
}

void Admin::ViewBankDatabase(void)
{
    // Send initial requests to the server
    m_request = "View Data Base";
    SendRequestToServer();
    // create a datastream to send the nedded info to the server to transfer the money.
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);
    cout << "=======================================================" << Qt::endl;
    QString DBType;
    // select which data base to show
    cout << "Please specify Which Data Base to show\n"
            "To show Admins Data Base press <" << ADMIN_USER <<">\n"
            "To show Standard Users Data Base press <" << STANDARD_USER << ">\n" << Qt::endl;
    cout << "Select>> "; cout.flush();
    cin >> DBType;
    cout << "=======================================================" << Qt::endl;
    if( (DBType.toInt() == ADMIN_USER ) )
    {
        DBType = "ADMIN";
    }else
        if( (DBType.toInt() == STANDARD_USER ) )
    {
        DBType = "STANDARD";
    }else
    {
        cout << "Wrong Entery" << Qt::endl;
        return;
    }
    // Send data to server
    outStream << DBType;
    // wait to write on socket
    socket.waitForBytesWritten();
    //wait for the respond from the server to view it to the client
    socket.waitForReadyRead();
    cout << "=======================================================" << Qt::endl;
}

void Admin::CreateNewUser(void)
{
    // Set Stream
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);

    QString UserMode,UserName,CancelBtn;
    // select user mode
    do{
        cout << "Please specify New User Mode\n"
                "For Admin Mode enter <" << ADMIN_USER <<">\n"
                "For Standard Mode enter <" << STANDARD_USER << ">\n"
                "User Mode>> "; cout.flush();
        cin >> UserMode;
        cout << "=======================================================" << Qt::endl;
        if( (UserMode.toInt() != ADMIN_USER ) && (UserMode.toInt() != STANDARD_USER ) )
        {
            cout << "Wrong Entery!\n"
                    "To Cancel press <" << CANCEL_OPERATION <<">\n"
                    "To Continue press any other key"<< Qt::endl;
            cout << "Key>> "; cout.flush();
            cin >> UserMode;
            cout << "=======================================================" << Qt::endl;
            if( UserMode.toInt() == CANCEL_OPERATION )
            {
                return;
            }
        }
    }while( (UserMode.toInt() != ADMIN_USER ) && (UserMode.toInt() != STANDARD_USER ) );

    // Set User Mode
    if(UserMode.toInt() == ADMIN_USER)
    {
        UserMode = "ADMIN";
    }else if(UserMode.toInt() == STANDARD_USER)
    {
        UserMode = "STANDARD";
    }else {
        qDebug() << "Error! Getting an unknown role,, returning to main menu..";
        return;
    }

    // take user name and send it with the user mode to server to make sure it exists
    do
    {
        // First request to find if user admin wants to update is found or not
        // Send initial requests to the server
        m_request = "Create New User";
        SendRequestToServer();

        // Take Data from the User
        cout << "Please Enter the New Account UserName you want to Create:" << Qt::endl;

        cout << "UserName To Create>> "; cout.flush();
        cin >> UserName;
        cout << "=======================================================" << Qt::endl;
        // look if the userName is found
        SearchUserName(UserMode,UserName);
        cout << "=======================================================" << Qt::endl;
        // Case user is found
        if(m_ServerRespond.toBool() == true)
        {
            cout << "This UserName Already Exists,\n"
                    "Please Choose another UserName" << Qt::endl;

            cout << "=======================================================" << Qt::endl;

            cout << "To Cancel operation press <" << CANCEL_OPERATION << ">\n"
                    "To Continue press any other key" << Qt::endl;

            cout << "Operation>> ";cout.flush();
            cin >> CancelBtn;
            cout << "=======================================================" << Qt::endl;
            if( CancelBtn.toInt() == CANCEL_OPERATION )
            {
                return;
            }
        }
    }while(m_ServerRespond.toBool() == true);
    // Take rest of New User Info
    QString NewUserFullName,FirstName,SecondName,NewUserAge,NewUserPassword;
    cout << "Please specify the Following Info To Create The Account" << Qt::endl;
    cout << "New User PASSWORD>> "; cout.flush();
    cin >> NewUserPassword;
    cout << "New User First Name>> "; cout.flush();
    cin >> FirstName;
    cout << "New User Second Name>> "; cout.flush();
    cin >> SecondName;
    NewUserFullName = FirstName + " " + SecondName;
    cout << "New User Age>> "; cout.flush();
    cin >> NewUserAge;
    // Send initial requests to server
    m_request ="Create New User";
    SendRequestToServer();
    // Send Secondary request
    m_request = "Create Now";
    outStream << m_request << UserMode << UserName << NewUserPassword
              << NewUserFullName << NewUserAge;

    if(UserMode.toUpper() == "STANDARD" )
    {
        QString NewUserBalance;
        cout << "New User Balance>> "; cout.flush();
        cin >> NewUserBalance;
        outStream << NewUserBalance;
    }
    socket.waitForBytesWritten();
    socket.waitForReadyRead();
    cout << "=======================================================" << Qt::endl;
    if(m_ServerRespond.toBool() == true)
    {
        cout<< UserName << " Create Successfully!" << Qt::endl;
    }else
    {
        cout << "Error Creating New User: " << UserName << Qt::endl;
    }
}

void Admin::DeleteUser(void)
{
    // Set Stream
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);
    //Take args needed from the user
    QString UserName, UserMode;
    // select user mode
    do{
        cout << "Please specify User Mode\n"
                "For Admin Mode enter <" << ADMIN_USER <<">\n"
                "For Standard Mode enter <" << STANDARD_USER << ">\n"
                "User Mode>> "; cout.flush();
        cin >> UserMode;
        cout << "=======================================================" << Qt::endl;
        if( (UserMode.toInt() != ADMIN_USER ) && (UserMode.toInt() != STANDARD_USER ) )
        {
            cout << "Wrong Entery!\n"
                    "To Cancel press <" << CANCEL_OPERATION <<">\n"
                    "To Continue press any other key"<< Qt::endl;
            cout << "Key>> "; cout.flush();
            cin >> UserMode;
            cout << "=======================================================" << Qt::endl;
            if( UserMode.toInt() == CANCEL_OPERATION )
            {
                return;
            }
        }
    }while( (UserMode.toInt() != ADMIN_USER ) && (UserMode.toInt() != STANDARD_USER ) );

    // Send initial request to server
    m_request = "Delete User";
    SendRequestToServer();

    if(UserMode.toInt() == ADMIN_USER )
    {
        UserMode = "ADMIN";
    }else
        if(UserMode.toInt() == STANDARD_USER )
    {
        UserMode = "STANDARD";
    }

    cout << "Please enter UserName to delete\n" << Qt::endl;
    cout << "UserName>> "; cout.flush();
    cin >> UserName;

    // Send on Stream
    outStream << UserMode << UserName;
    socket.waitForBytesWritten();
    // Wait for server respond
    socket.waitForReadyRead();
    cout << "=======================================================" << Qt::endl;
    bool isDeleted = m_ServerRespond.toBool();
    if(isDeleted)
    {
        cout << UserName <<" was deleted successfully" << Qt::endl;
    }else{
        cout << UserName << " is not found in Database!" << Qt::endl;
    }
}

void Admin::UpdateUser(void)
{
    // Set Stream
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);
    QString UserMode,UserName,CancelBtn;
    // select user mode
    do{
        cout << "Please specify User Mode\n"
                "For Admin Mode enter <" << ADMIN_USER <<">\n"
                "For Standard Mode enter <" << STANDARD_USER << ">\n"
                "User Mode>> "; cout.flush();
        cin >> UserMode;
        cout << "=======================================================" << Qt::endl;
        if( (UserMode.toInt() != ADMIN_USER ) && (UserMode.toInt() != STANDARD_USER ) )
        {
            cout << "Wrong Entery!\n"
                    "To Cancel press <" << CANCEL_OPERATION <<">\n"
                    "To Continue press any other key"<< Qt::endl;
            cout << "Key>> "; cout.flush();
            cin >> UserMode;
            cout << "=======================================================" << Qt::endl;
            if( UserMode.toInt() == CANCEL_OPERATION )
            {
                return;
            }
        }
    }while( (UserMode.toInt() != ADMIN_USER ) && (UserMode.toInt() != STANDARD_USER ) );

    if(UserMode.toInt() == ADMIN_USER)
    {
        UserMode = "ADMIN";
    }else if(UserMode.toInt() == STANDARD_USER)
    {
        UserMode = "STANDARD";
    }else {
        qDebug() << "Error! Getting an unknown role,, returning to main menu..";
        return;
    }
    // take user name and send it with the user mode to server to make sure it exists
    do
    {
        // First request to find if user admin wants to update is found or not
        // Send initial requests to the server
        m_request = "Update User";
        SendRequestToServer();

        // Take Data from the User
        cout << "Please Enter the Account UserName you want to Update:" << Qt::endl;

        cout << "UserName To Update>> "; cout.flush();
        cin >> UserName;
        cout << "=======================================================" << Qt::endl;

        SearchUserName(UserMode,UserName);
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
            cout << "=======================================================" << Qt::endl;
            if( CancelBtn.toInt() == CANCEL_OPERATION )
            {
                return;
            }
        }
    }while(m_ServerRespond.toBool() == false);

    QString FieldToUpdate, ContKey;
    bool ok = false;
    // After UserMode is correct and UserName is found,, let the Admin choose which field to update
    do
    {
        //show fields that can be update
        cout << "Specify which field you want to update:\n"
                "To Update Full name press <" << FULL_NAME_FIELD << ">\n"
                "To Update Password press <" << PASSWORD_FIELD << ">\n"
                "To Update Age press <" << AGE_FIELD << ">" << Qt::endl;
        if(UserMode == "STANDARD")
        {
                cout << "To Update Balance press <" << BALANCE_FIELD << ">" << Qt::endl;
        }
        cout << "Field ID>> "; cout.flush();
        cin >> FieldToUpdate;
        cout << "=======================================================" << Qt::endl;
        switch (FieldToUpdate.toInt()) {
        case FULL_NAME_FIELD:
            FieldToUpdate = "Full Name";
            ok = true;
            break;
        case PASSWORD_FIELD:
            FieldToUpdate = "Password";
            ok = true;
            break;
        case AGE_FIELD:
            FieldToUpdate = "Age";
            ok = true;
            break;
        case BALANCE_FIELD:
            if(UserMode == "STANDARD")
            {
                FieldToUpdate = "Balance";
                ok = true;
                break;
            }
        default:
            cout << "Incorrect Field ID, Please choose again!" << Qt::endl;
            ok = false;
            break;
        }
        cout << "=======================================================" << Qt::endl;
        // if there's no error send take the new field value and send it
        if(ok)
        {
            QString FieldNewValue;
            cout << "Please Enter New " << FieldToUpdate << " To update: " << Qt::endl;

            if(FieldToUpdate == "Full Name")
            {
                // FieldNewValue = cin.readLine();
                QString firstName,SecondName;
                cout << "Enter New First Name>> ";cout.flush();
                cin >> firstName;
                cout << "Enter New Last Name>> ";cout.flush();
                cin >> SecondName;
                FieldNewValue = firstName + " " + SecondName;
            }else
            {
                cout << "New Value>> "; cout.flush();
                cin >> FieldNewValue;
            }
            // Send initial requests to the server
            m_request = "Update User";
            SendRequestToServer();
            // Send Second Request to the server
            m_request = "Make The Update";
            outStream << m_request << UserMode << UserName << FieldToUpdate << FieldNewValue;
            // wait to send data to server
            socket.waitForBytesWritten();
            // wait to receive data from server
            socket.waitForReadyRead();
            if(m_ServerRespond.toBool() == true)
            {
                cout << FieldToUpdate << " Updated successfully" << Qt::endl;
            }else{
                cout << "Error Updating " << FieldToUpdate;
            }
            cout << "=======================================================" << Qt::endl;
        }
        cout << "To update another Field in User: " << UserName <<
                " Press <" << TO_CONTINUE << ">\n"
                "To return to main menu press any other key" << Qt::endl;
        cout << "Key>> "; cout.flush();
        cin >> ContKey;
        cout << "=======================================================" << Qt::endl;
    }while( ContKey.toInt() == TO_CONTINUE );

}

void Admin::ViewTransactionHistory(void)
{
    // Send initial requests to server
    m_request = "Get Trans History";
    SendRequestToServer();
    cout << "=======================================================" << Qt::endl;
    // create a datastream to send the nedded info to the server to transfer the money.
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);
    QString UserName,Count;
    // Read data from the user
    cout << "Transaction History>> <UserName> <Count To Show>" << Qt::endl;
    cout << "Transaction History>> "; cout.flush();
    cin >> UserName >> Count;
    cout << "=======================================================" << Qt::endl;
    // Send data to Server
    outStream << UserName << Count;
    // wait to write to the server
    socket.waitForBytesWritten();
    // wait to receive data from the server
    socket.waitForReadyRead();
    cout << "=======================================================" << Qt::endl;
}

void Admin::SendRequestToServer(void)
{
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);
    outStream << m_request << m_role;
}

void Admin::readyRead()
{
    QDataStream inStream(&socket);
    inStream.setVersion(QDataStream::Qt_6_6);
    bool Response = false;

    if( m_request == "Login")
    {
        // Receive from the Data from the Socket Stream
        inStream >> Response;
        // Set Values of login return
        m_ServerRespond.setValue(Response);
    }
    else if(m_request == "Get Account Number")
    {
        QString AccNum;
        inStream >> Response >> AccNum;
        m_ServerRespond.setValue(Response);
        m_AccountNumber = AccNum;
    }else
        if(m_request == "View Account Balance")
    {
        QString balance;
        inStream >> Response >> balance;
        m_ServerRespond.setValue(Response);
        m_Balance = balance;
    }else
        if(m_request == "View Data Base")
    {
        QString DataBase;
        inStream >> Response >> DataBase;
        if(Response == true)
        {
            cout << "Printing Data Base : \n"
                 << DataBase << Qt::endl;
        }
    }else
        if(m_request == "Create Now")
    {
        // Take Response from the user
        inStream >> Response;
        m_ServerRespond.setValue(Response);
    }else
        if(m_request == "Delete User")
    {
        inStream >> Response;
        m_ServerRespond.setValue(Response);
    }else
        if(m_request == "Get Trans History")
    {
        QString Data;
        inStream >> Response >> Data;
        if(!Response)
        {
            cout << Data << Qt::endl;
        }else{
            cout << "Transaction History :\n" << Data << Qt::endl;
        }
    }else
        if( m_request == "CHECK USER IS FOUND")
    {
        // read response from the server and set it
        inStream >> Response;
        m_ServerRespond.setValue(Response);
    }else
        if(m_request == "Make The Update")
    {
        //Receive the respond from the server and set it
        inStream >> Response;
        m_ServerRespond.setValue(Response);
    }
}

bool Admin::Login(void)
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
    quint8 count =0;
    while(!LoginOk)
    {
        count++;
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

void Admin::SearchUserName(const QString UserMode, const QString UserName)
{
    // Set Stream
    QDataStream outStream(&socket);
    outStream.setVersion(QDataStream::Qt_6_6);
    // Set first request to check if username is found
    m_request = "CHECK USER IS FOUND";
    // Send user name to server to check account is found
    outStream << m_request << UserMode << UserName;
    // wait to send data to the server
    socket.waitForBytesWritten();
    // wait to receive data from the server
    socket.waitForReadyRead();
}

void Admin::start(void)
{
    QString CommandToExcute;//,ToExit;
    while(true)
    {
        cout << "=======================================================" << Qt::endl;
            // let Admin choose what to do
        cout <<
            "Choose from the list:\n1-Get Account Number\n2-View Account Balance\n"
            "3-Get Transaction History\n4-View Bank DataBase\n"
            "5-Create New User\n"
            "6-Delete User\n7-Update User\n8-Exit Application" << Qt::endl;
        cout << "Command ID>> "; cout.flush();
        cin >> CommandToExcute;
        cout << "=======================================================" << Qt::endl;

        switch(CommandToExcute.toInt())
        {
        case 1:
            GetAccNo(); // Done
            break;
        case 2:
            ViewAccountBalance(); // Done
            break;
        case 3:
            ViewTransactionHistory(); // Done
            break;
        case 4:
            ViewBankDatabase(); //DOne
            break;
        case 5:
            CreateNewUser();
            break;
        case 6:
            DeleteUser();   // Done
            break;
        case 7:
            UpdateUser(); // Done
            break;
        case 8:
            exit(0);
        default:
            cout << "Wrong Entery Please Choose again!" << Qt::endl;
            break;
        }
        cout << "=======================================================" << Qt::endl;
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

void Admin::connectToHost(QString host, quint16 port)
{
    if(socket.isOpen()) disconnect();
    socket.connectToHost(host,port);
}

void Admin::disconnect()
{
    socket.close();
    socket.waitForDisconnected();
}

void Admin::connected()
{
    QTextStream input(stdin, QIODevice::ReadOnly);
    QString userInput = input.readLine().trimmed();
    socket.write(userInput.toUtf8());
}

void Admin::disconnected()
{
    qDebug() << "Disconnected";
}

void Admin::error(QAbstractSocket::SocketError socketerror)
{
    qDebug() << "Error:" << socketerror << socket.errorString();
}

void Admin::stateChanged(QAbstractSocket::SocketState socketstate)
{
    QMetaEnum metaenum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    QString str= metaenum.valueToKey(socketstate);
}




