#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QString>
#include "IDataBase.h"

class DataBaseFactory : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseFactory(QObject* parent = 0);
    ~DataBaseFactory();
    IDataBase *createSqliteDataBase(const QString dbPath = "GetInfoDB.sqlite");

private:
    IDataBase* dataBase;
};

#endif // DATABASEMANAGER_H
