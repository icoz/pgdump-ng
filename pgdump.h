#ifndef PGDUMP_H
#define PGDUMP_H

#include <QObject>
#include <QtSql>

class Pgdump : public QObject
{
    Q_OBJECT
public:
    //explicit Pgdump(QObject *parent = 0);
    Pgdump(QString user="postgres",QString pass="postgres",QString host="localhost",int port=5432,QObject *parent = 0);
    void setHost(QString host="localhost") {db.setHostName(host);}
    void setPort(QString port="5432") {db.setPort(port.toInt());}
    void setPort(int port=5432) {db.setPort(port);}
    void setUser(QString user="user") {db.setUserName(user);}
    void setPassword(QString pass="pass") {db.setPassword(pass);}
    bool tryOpen() {return db.open();}
    QStringList getDatabases();
    QStringList getTables(QString dbname);
signals:

public slots:
private:
    QSqlDatabase db;
};

#endif // PGDUMP_H
