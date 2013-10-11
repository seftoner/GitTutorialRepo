#include <QDebug>
#include <QSqlQuery>

#include "DataBaseFactory.h"
#include "SqliteDB.h"

DataBaseFactory::DataBaseFactory(QObject *parent) :
    QObject(parent)
{
}

DataBaseFactory::~DataBaseFactory()
{
    delete dataBase;
}

IDataBase* DataBaseFactory::createSqliteDataBase(const QString dbPath)
{
    dataBase = new SqliteDB(dbPath);
    return dataBase;
}
