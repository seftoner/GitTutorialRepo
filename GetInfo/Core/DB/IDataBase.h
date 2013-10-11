#ifndef IDATABASE_H
#define IDATABASE_H

#include "../Items/SearchParameters.h"
#include "../Items/ResultItem.h"
#include "../Items/HistoryItem.h"
#include "CountryCityModelGenerator.h"
#include "KnowledgeModelGenerator.h"
#include <QAbstractItemModel>

class IDataBase
{
public:
    virtual ~IDataBase() {}
    virtual bool addNewHistoryRecord(const SearchParameters& searchParameters,
                                     const QList<ResultItem>& resultQueryList) = 0;
    virtual bool deleteHistoryRow(const int id) = 0;
    virtual bool deleteHistoryRows(const QVector<int>& ids) = 0;
    virtual QList<HistoryItem> getQueryHistory() = 0;
    virtual QList<ResultItem> getQueryResults(const int id) = 0;
    virtual HistoryItem getLastHistoryRow() = 0;
    virtual QSharedPointer<CountryCityModelGenerator> getCountryCityGen() = 0;
    virtual QSharedPointer<KnowledgeModelGenerator> getKnowledgeGen() = 0;

};

#endif // IDATABASE_H
