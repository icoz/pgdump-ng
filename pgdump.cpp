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
        //qDebug() << "db connected!";
        QSqlQuery q(db);
        QString cmd = "SELECT d.datname FROM pg_catalog.pg_database d ORDER BY 1;";
        if (q.exec(cmd)){
            //qDebug("query runned well!");
            while (q.next()){
                sl.append(q.value(0).toString());
            }
        }
        db.close();
    }
    //qDebug() << sl;
    return sl;
}

QStringList Pgdump::getTables(QString dbname)
{
    QStringList sl;
    db.setDatabaseName(dbname);
    if (db.open()){
        //qDebug() << "db connected!";
        QSqlQuery q(db);
        QString cmd = "select c.relname from  pg_catalog.pg_class c left join pg_catalog.pg_namespace n on n.oid= c.relnamespace where c.relkind = 'r' and n.nspname <> 'pg_catalog' and n.nspname <> 'information_schema' and n.nspname !~ '^pg_toast' and pg_catalog.pg_table_is_visible(c.oid) ORDER BY 1;";
        if (q.exec(cmd)){
            //qDebug("query runned well!");
            while (q.next()){
                sl.append(q.value(0).toString());
            }
        }
        db.close();
    }
    return sl;
}

QStringList Pgdump::getSchemas(QString dbname)
{
    QStringList sl;
    db.setDatabaseName(dbname);
    if (db.open()){
        //qDebug() << "db connected!";
        QSqlQuery q(db);
        QString cmd = "select n.nspname from pg_catalog.pg_namespace n where (n.nspname !~ '^pg_temp_' OR n.nspname = (pg_catalog.current_schemas(true))[1]) order by 1;";
        if (q.exec(cmd)){
            //qDebug("query runned well!");
            while (q.next()){
                sl.append(q.value(0).toString());
            }
        }
        db.close();
    }
    return sl;
}

/*
SELECT c.relname as "Name",
  CASE c.relkind WHEN 'r' THEN 'table' WHEN 'v' THEN 'view' WHEN 'i' THEN 'index' WHEN 'S' THEN 'sequence' WHEN 's' THEN 'special' END as "Type",
  pg_catalog.pg_get_userbyid(c.relowner) as "Owner"
FROM pg_catalog.pg_class c
     LEFT JOIN pg_catalog.pg_namespace n ON n.oid = c.relnamespace
WHERE c.relkind IN ('r','')
      AND n.nspname <> 'pg_catalog'
      AND n.nspname <> 'information_schema'
      AND n.nspname !~ '^pg_toast'
  AND pg_catalog.pg_table_is_visible(c.oid)
ORDER BY 1;


//get tables
SELECT n.nspname as "Schema",
  c.relname as "Name",
  CASE c.relkind WHEN 'r' THEN 'table' WHEN 'v' THEN 'view' WHEN 'i' THEN 'index' WHEN 'S' THEN 'sequence' WHEN 's' THEN 'special' END as "Type",
  pg_catalog.pg_get_userbyid(c.relowner) as "Owner"
FROM pg_catalog.pg_class c
     LEFT JOIN pg_catalog.pg_namespace n ON n.oid = c.relnamespace
WHERE c.relkind IN ('r','')
      AND n.nspname <> 'pg_catalog'
      AND n.nspname <> 'information_schema'
      AND n.nspname !~ '^pg_toast'
  AND pg_catalog.pg_table_is_visible(c.oid)
ORDER BY 1,2;

select n.nspname from pg_catalog.pg_namespace n where (n.nspname !~ '^pg_temp_' OR n.nspname = (pg_catalog.current_schemas(true))[1]) order by 1;
*/
