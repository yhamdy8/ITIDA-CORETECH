#include <QCoreApplication>
#include "server.h"
#include "JsonHandler.h"
#include <QThread>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    server.start();


    return a.exec();
}
