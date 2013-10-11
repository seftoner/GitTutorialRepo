#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include "SearchParameters.h"
#include <QDateTime>

class HistoryItem
{
public:
    HistoryItem() {}
    HistoryItem(const int id, const QDateTime dateTime, const SearchParameters parameters) :
        id(id), date(dateTime), parameters(parameters) {}

public:
    int id;
    QDateTime date;
    SearchParameters parameters;
};

Q_DECLARE_METATYPE(HistoryItem)


#endif // HISTORYITEM_H
