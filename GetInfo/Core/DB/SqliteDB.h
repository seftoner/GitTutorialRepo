#ifndef SQLITEDB_H
#define SQLITEDB_H

#include "IDataBase.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>

class SqliteDB : public IDataBase, QObject
{
public:
    SqliteDB();
    SqliteDB(const QString dbName);
    ~SqliteDB();

    bool addNewHistoryRecord(const SearchParameters& searchParameters,
                             const QList<ResultItem>& resultQueryList) override;
    bool deleteHistoryRow(const int id) override;
    bool deleteHistoryRows(const QVector<int>& ids) override;
    QList<HistoryItem> getQueryHistory() override;
    QList<ResultItem> getQueryResults(const int id) override;
    HistoryItem getLastHistoryRow() override;
    QSharedPointer<CountryCityModelGenerator> getCountryCityGen() override;
    QSharedPointer<KnowledgeModelGenerator> getKnowledgeGen() override;

private:
    int lastInsertedId;
    QString dbName;
    QSqlDatabase dataBase;
    QSqlQuery query;

    QList<HistoryItem> queryHistoryList;
    QList<ResultItem> queryResultList;
    HistoryItem lastHistoryRow;

    static const int kEmptyId = 0;
    const QString dbConnectionOption;

private:
    void openDB();
    void createDB();
    bool addQueryHistoryRecord(const SearchParameters& searchParameters);
    bool addQueryResultRecord(const QList<ResultItem>& resultQueryList, const int id);
};

#endif // SQLITEDB_H
