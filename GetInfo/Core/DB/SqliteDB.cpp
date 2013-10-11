#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include "SqliteDB.h"
#include "../Items/ResultItem.h"
#include "../Items/HistoryItem.h"

#include "SqliteQuery.h"
#include <QSqlQueryModel>
#include <QSqlRecord>

SqliteDB::SqliteDB()
{
}

SqliteDB::SqliteDB(const QString dbName) :
    dbName(dbName),
    dataBase(QSqlDatabase::addDatabase("QSQLITE")),
    dbConnectionOption("foreign_keys = ON")
{
    if(QFile::exists(dbName))
    {
        openDB();
    }
    else
    {
        createDB();
    }
}

SqliteDB::~SqliteDB()
{
}

bool SqliteDB::addNewHistoryRecord(const SearchParameters& searchParameters,
                                   const QList<ResultItem>& resultQueryList)
{
    qDebug() << "--> SqliteDB::addNewHistoryRecord";
    if(!addQueryHistoryRecord(searchParameters) ||
            !addQueryResultRecord(resultQueryList, lastInsertedId))
    {
        qDebug() << query.lastError();
        return false;
    }

    return true;
}

bool SqliteDB::deleteHistoryRow(const int id)
{
    query.prepare(kRemoveQueryHistroyRow);
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool SqliteDB::deleteHistoryRows(const QVector<int>& ids)
{
    for(const auto id : ids)
    {
        if(!deleteHistoryRow(id))
        {
            return false;
        }
    }

    return true;
}

QList<HistoryItem> SqliteDB::getQueryHistory()
{
    query = QSqlQuery(dataBase);

    if(!query.exec(kGetAllQueryHistroy))
    {
        qDebug() <<  query.lastError();
    }

    while (query.next())
    {
        SearchParameters parameters(query.value("desiredUniversity").toString(),
                                    query.value("desiredKnowledge").toString(),
                                    query.value("desiredCity").toString(),
                                    query.value("desiredCountry").toString(),
                                    query.value("desiredResourceName").toStringList());
        HistoryItem queryItem(query.value("id").toInt(),
                              query.value("queryDate").toDateTime(),
                              parameters);

        queryHistoryList << queryItem;
    }

    if(queryHistoryList.size() > 0)
    {
        lastHistoryRow = queryHistoryList.last();
    }

    return queryHistoryList;
}

QList<ResultItem> SqliteDB::getQueryResults(const int id)
{
    query.prepare(kGetQueryResultById);
    query.bindValue(":id", id);

    if(!query.exec())
    {
        qDebug() <<  query.lastError();
    }

    queryResultList.clear();

    while (query.next())
    {
        ResultItem queryItem(query.value("name").toString(),
                             query.value("surname").toString(),
                             query.value("position").toString(),
                             query.value("city").toString(),
                             query.value("university").toString(),
                             query.value("phone").toString(),
                             query.value("email").toString(),
                             query.value("skype").toString(),
                             query.value("profileUrl").toString(),
                             query.value("searchResourceName").toString(),
                             query.value("id").toInt());

        queryResultList << queryItem;
    }

    return queryResultList;
}

HistoryItem SqliteDB::getLastHistoryRow()
{
    return lastHistoryRow;
}

QSharedPointer<CountryCityModelGenerator> SqliteDB::getCountryCityGen()
{
    return QSharedPointer<CountryCityModelGenerator>
            (new CountryCityModelGenerator(&dataBase));
}

QSharedPointer<KnowledgeModelGenerator> SqliteDB::getKnowledgeGen()
{
    return QSharedPointer<KnowledgeModelGenerator>
            (new KnowledgeModelGenerator(&dataBase));
}

void SqliteDB::openDB()
{
    qDebug() << "--> SqliteDB::openDB";
    dataBase.setDatabaseName(dbName);
    if(dataBase.open())
    {
        query = QSqlQuery(dataBase);
        query.exec(kFrnKeys);
    }
    else
    {
        qDebug() <<  dataBase.lastError();
    }
}

void SqliteDB::createDB()
{
    qDebug() << "--> SqliteDB::createDB";
    dataBase.setDatabaseName(dbName);
    dataBase.setConnectOptions(dbConnectionOption);
    if(!dataBase.open())
    {
        qDebug() << dataBase.lastError().text();
    }
    query = QSqlQuery(dataBase);

    if (!query.exec(kFrnKeys) ||
            !query.exec(kCreateQueryHistroyTable) ||
            !query.exec(kCreateQueryResultTable) ||
            !query.exec(kCreateCountriesTable) ||
            !query.exec(kCreateCitiesTable))
    {
        qDebug() << dataBase.lastError().text();
    }
}

bool SqliteDB::addQueryHistoryRecord(const SearchParameters& searchParameters)
{
    HistoryItem historyItem(kEmptyId, QDateTime::currentDateTime(), searchParameters);

    query.prepare(kAddNewQueryHistoryRecord);
    query.bindValue(":queryDate", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":desiredKnowledge", searchParameters.knowledge);
    query.bindValue(":desiredUniversity", searchParameters.univercity);
    query.bindValue(":desiredCity", searchParameters.city);
    query.bindValue(":desiredCountry", searchParameters.country);
    query.bindValue(":desiredResourceName", searchParameters.searchResName.join(","));


    if(!query.exec())
    {
        qDebug() << query.lastError();
        return false;
    }

    lastInsertedId = historyItem.id = query.lastInsertId().toInt();
    queryHistoryList.append(historyItem);
    lastHistoryRow = historyItem;

    return true;
}

bool SqliteDB::addQueryResultRecord(const QList<ResultItem>& resultQueryList,
                                    const int id)
{
    dataBase.transaction();
    query.prepare(kAddNewQueryResultsRecords);
    for (auto item : resultQueryList)
    {
        query.bindValue(":name", item.name);
        query.bindValue(":surname", item.surname);
        query.bindValue(":position", item.position);
        query.bindValue(":city", item.city);
        query.bindValue(":university", item.university);
        query.bindValue(":phone", item.phone);
        query.bindValue(":email", item.email);
        query.bindValue(":skype", item.skype);
        query.bindValue(":profileUrl",item.profileUrl);
        query.bindValue(":searchResourceName", item.searchResourceName);
        query.bindValue(":queryHistoryId", id);

        if(!query.exec())
        {
            dataBase.rollback();
        }
    }
    if(!dataBase.commit())
    {
        dataBase.rollback();
        qDebug() << query.lastError();
        return false;
    }
    return true;
}
