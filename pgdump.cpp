#include "pgdump.h"
#include <QtDebug>

/*Pgdump::Pgdump(QObject *parent) :
    QObject(parent)
{
    db = QSqlDatabase::addDatabase("QPSQL");
}//*/

Pgdump::Pgdump(QString user,QString pass,QString host,int port,QObject *parent)
    : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setPort(port);
    db.setUserName(user);
    db.setPassword(pass);
}

QStringList Pgdump::getDatabases()
{
    QStringList sl;
    db.setDatabaseName("postgres");
    if (db.open()){
        qDebug() << "db connected!";
        QSqlQuery q(db);
        QString cmd = "SELECT d.datname FROM pg_catalog.pg_database d ORDER BY 1;";
        if (q.exec(cmd)){
            qDebug("query runned well!");
            while (q.next()){
                sl.append(q.value(0).toString());
            }
        }
        db.close();
    }
    qDebug() << sl;
    return sl;
}
