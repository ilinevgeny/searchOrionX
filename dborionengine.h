#ifndef DBORIONENGINE_H
#define DBORIONENGINE_H
#include <QObject>
#include <QSqlDatabase>

struct DBParams
{
    QString Driver;
    QString Server;
    QString DBName;
    int Port;
    QString UserName;
    QString Password;
};

class DBOrionEngine : public QObject
{
    Q_OBJECT
public:
    DBOrionEngine(QString driver, QString server, QString dbName, int port, QString userName, QString password);
    void Connect();
    void Diconnect();
    bool statusConnect;

protected:
    DBParams DBParams;
    QSqlDatabase db;
    void setDBParams(QString, QString, QString, int, QString, QString);

};

#endif // DBORIONENGINE_H
