#ifndef COMLETIONCHECKER_H
#define COMLETIONCHECKER_H

#include <QObject>
#include "Items/ResultItem.h"
#include "Items/PluginInfoItem.h"
#include <QSharedPointer>
#include <QScopedPointer>
#include <QList>
#include <QStringList>

class CompletionChecker : public QObject
{
    Q_OBJECT
public:
    explicit CompletionChecker(QObject *parent = 0);
    ~CompletionChecker();

    bool check(QSharedPointer<QList<ResultItem> > &currentResultList);
    void addNameOfReadyPlugin(QString pluginName);
    void clear();
    bool isEmptyReadyPluginsList();
private:
    QScopedPointer<QStringList> readyPluginsList;
    QScopedPointer<QStringList> pluginsSourceNames;

signals:

public slots:

};

#endif // COMLETIONCHECKER_H
