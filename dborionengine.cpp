#include "dborionengine.h"
#include <QDebug>
#include <QSqlError>
DBOrionEngine::DBOrionEngine(QString driver, QString server, QString dbName, int port, QString userName, QString password)
{
    setDBParams(driver, server, dbName, port, userName, password);
    this->statusConnect = false;
}

void DBOrionEngine::setDBParams(QString driver, QString server, QString dbName, int port, QString userName, QString password)
{
    DBParams.Driver = driver;
    DBParams.Server = server;
    DBParams.DBName = dbName;
    DBParams.Port = port;
    DBParams.UserName = userName;
    DBParams.Password = password;

}

void DBOrionEngine::Diconnect()
{
    db.close();
}

void DBOrionEngine::Connect()
{

    db = QSqlDatabase::addDatabase(DBParams.Driver);
    db.setHostName(DBParams.Server);
    db.setPort(DBParams.Port);
    db.setDatabaseName(DBParams.DBName);
    db.setUserName(DBParams.UserName);
    db.setPassword(DBParams.Password);

    if(db.open())
    {
        this->statusConnect = true;
        qDebug() << "database open";
    } else {
       qDebug() << db.lastError();
    }
}
