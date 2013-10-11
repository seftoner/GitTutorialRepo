#ifndef PLUGINPROCESSOR_H
#define PLUGINPROCESSOR_H

#include "Items/ResultItem.h"
#include "Items/SearchParameters.h"
#include "PluginInterface.h"
#include "CompletionChecker.h"
#include <QSharedPointer>

class QPluginLoader;

class PluginProcessor : public QObject
{
Q_OBJECT
public:

    explicit PluginProcessor(QObject *parent = 0);
    ~PluginProcessor();

    QSharedPointer<QList<QSharedPointer<PluginInfoItem> > > getPluginsList();
    void search(const SearchParameters& searchParameters);
signals:
    void addResults(QSharedPointer<QList<ResultItem> >);
    void pluginErrorMessage(const QString& errorMsg);
    void readyStatusChanged();
    void pluginsResultFinished();

public slots:
    void setResultData(QSharedPointer<QList<ResultItem> > currentResultList);

private:
    bool init();
    QList<PluginInterface *> interfacesList;
    QPluginLoader *pluginLoader;
    CompletionChecker * completionChecker;

    QSharedPointer<QList<ResultItem> > resultList;
    QSharedPointer<QList<QSharedPointer<PluginInfoItem> > > pluginList;
};

#endif // PLUGINPROCESSOR_H
