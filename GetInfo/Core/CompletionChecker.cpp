#include "CompletionChecker.h"

CompletionChecker::CompletionChecker(QObject *parent) :
    QObject(parent)
{
    pluginsSourceNames.reset(new QStringList());
    readyPluginsList.reset(new QStringList());
}

CompletionChecker::~CompletionChecker()
{
}

bool CompletionChecker::check(QSharedPointer<QList<ResultItem> > &currentResultList)
{
    currentResultList->first();
    if (!pluginsSourceNames->contains(currentResultList->first().searchResourceName))
    {
        pluginsSourceNames->append(currentResultList->first().searchResourceName);
        if (readyPluginsList->size() == pluginsSourceNames->size())
        {
            return true;
        }
    }
    return false;
}

void CompletionChecker::addNameOfReadyPlugin(QString pluginName)
{
    readyPluginsList->append(pluginName);
}

void CompletionChecker::clear()
{
    pluginsSourceNames->clear();
    readyPluginsList->clear();
}

bool CompletionChecker::isEmptyReadyPluginsList()
{
    return readyPluginsList->isEmpty();
}

