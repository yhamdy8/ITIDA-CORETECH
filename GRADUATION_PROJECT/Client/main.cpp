#include <QCoreApplication>
#include <QDebug>
#include "user.h"
#include "admin.h"
#include <windows.h>
#include <QTextStream>
#include <QTcpSocket>

#define IP_ADDRESS "127.0.0.1"
#define PORT 1234

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString UserRole;

    QTextStream cin(stdin);
    QTextStream cout(stdout);
    do
    {
        cout << "=======================================================" << Qt::endl;
        cout << "Welcome To Banking Application!\n"
                "For Admin User press <" << ADMIN_USER << ">\n"
                "For Standared User press <" << STANDARD_USER << ">\n"
                "To Quit press <" << EXIT_COMMAND << ">" << Qt::endl;
        cout << "UserMode>> "; cout.flush();
        cin >> UserRole;
        cout << "=======================================================" << Qt::endl;
        if( (UserRole.toInt() != STANDARD_USER) &&
            (UserRole.toInt() != ADMIN_USER) &&
            (UserRole.toInt() != EXIT_COMMAND) )
        {
            cout << "Invalid input, Please choose a valid User Mode ID" << Qt::endl;
        }
    }while((UserRole.toInt() != STANDARD_USER) &&
             (UserRole.toInt() != ADMIN_USER) &&
             (UserRole.toInt() != EXIT_COMMAND));
    // Select User Mode
    if(UserRole.toInt() == STANDARD_USER )
    {
        User user;
        user.connectToHost(IP_ADDRESS, PORT);
        bool LoginOK = false;
        do
        {
            LoginOK = user.Login();
            cout << "=======================================================" << Qt::endl;
            if(!LoginOK)
            {
                cout << "User is not found" << Qt::endl;;
            }
        }while(!LoginOK);
        cout << "=======================================================" << Qt::endl;
        cout << "Welcome!" << Qt::endl;
        user.start();
    }else
        if(UserRole.toInt() == ADMIN_USER )
        {
            Admin admin;
            admin.connectToHost( IP_ADDRESS, PORT );
            bool LoginOK = false;
            do
            {
                LoginOK = admin.Login();
                cout << "=======================================================" << Qt::endl;
                if(!LoginOK)
                {
                    cout << "User is not found" << Qt::endl;;
                }
            }while(!LoginOK);
            cout << "=======================================================" << Qt::endl;
            cout << "Welcome!" << Qt::endl;
            admin.start();
        }
        else
            if(UserRole.toInt()== EXIT_COMMAND)
            {
                cout << "Thank you for using Bank App" << Qt::endl;
                exit(0);
            }
            else
            {
                qDebug() <<"Error in choosing role!";
            }
    return a.exec();
}

