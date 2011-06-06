#ifndef PGDUMP_H
#define PGDUMP_H

#include <QObject>
#include <QtSql>

class Pgdump : public QObject
{
    Q_OBJECT
public:
    explicit Pgdump(QObject *parent = 0)
    {
        db = QSqlDatabase::addDatabase("QPSQL");
    }
    void setHost(QString host="localhost") {db.setHostName(host);}
    void setPort(QString port="5432") {db.setPort(port.toInt());}
    void setPort(int port=5432) {db.setPort(port);}
    void setUser(QString user="user") {db.setUserName(user);}
    void setPassword(QString user="pass") {db.setPassword(pass);}
    QStringList getDatabases();
signals:

public slots:
private:
    QSqlDatabase db;
};

#endif // PGDUMP_H
