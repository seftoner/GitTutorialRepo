#include "PluginProcessor.h"
#include <QMessageBox>
#include <QtWidgets>
#include <QDebug>
#include <QThread>

PluginProcessor::PluginProcessor(QObject *parent) :
    QObject(parent)
{
    qDebug("PluginProcessor Constructor");
    pluginList = QSharedPointer<QList<QSharedPointer<PluginInfoItem> > >(new QList<QSharedPointer<PluginInfoItem> >);
    resultList = QSharedPointer<QList<ResultItem>>(new QList<ResultItem>);

    if (!init())
    {
        qDebug("Could not load the plugin");
    }

}

PluginProcessor::~PluginProcessor()
{
    qDebug("PluginProcessor Destructor");
    delete pluginLoader;
}

bool PluginProcessor::init()
{
    pluginLoader = new QPluginLoader();
    completionChecker = new CompletionChecker(this);
    qDebug("--> PluginProcessor::init()");
    QDir pluginsDir(qApp->applicationDirPath());
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
    pluginsDir.cd("plugins");
    int pluginsCount = 0;
    pluginList->clear();
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        pluginLoader->setFileName(pluginsDir.absoluteFilePath(fileName));
        pluginLoader->load();
        QObject *plugin = pluginLoader->instance();
        if (plugin)
        {
            PluginInterface *pluginInterface = qobject_cast<PluginInterface *>(plugin);
            if (pluginInterface)
            {
                qDebug() << "Success load plugin searchInterface " + QString(fileName);
                qDebug() << QString(pluginsDir.absoluteFilePath(fileName));
                bool a = QObject::connect(pluginInterface,
                                          SIGNAL(endParcing(QSharedPointer<QList<ResultItem>>)),
                                          this, SLOT(setResultData(QSharedPointer<QList<ResultItem>>)));

                connect(pluginInterface, SIGNAL(newErrorMessage(const QString& )),
                        this, SIGNAL(pluginErrorMessage(const QString& )));
                connect(pluginInterface, SIGNAL(readyStatusChanged()), this ,
                        SIGNAL(readyStatusChanged()));               

                qDebug() << "Success connect to plugin "<< pluginInterface->getPluginInfo()->pluginName << " signal? " << a;
                pluginList->append(pluginInterface->getPluginInfo());
                interfacesList.append(pluginInterface);
                ++pluginsCount;
            }
            else
            {
                qDebug() << "False loading plugin interface " << QString(fileName);
            }
        }
    }

    if (pluginsCount > 0)
    {
        qDebug() << "Active Plugins Count: " << pluginList->count();
        return true;
    }
    return false;
}

QSharedPointer<QList<QSharedPointer<PluginInfoItem> > > PluginProcessor::getPluginsList()
{
    qDebug() << "--> PluginProcessor::getPluginsList()";
    qDebug() << "Active Plugins Count: " << pluginList->count();
    return pluginList;
}

void PluginProcessor::search(const SearchParameters& searchParameters)
{
    qDebug() << "--> PluginProcessor::search(const SearchParameters& searchParameters)";
    resultList->clear();
    completionChecker->clear();
    qDebug() << "All Plugins Search Results Count: " << resultList->size();
    qDebug() << "All interfaces List Count: " << interfacesList.size();

    for (PluginInterface *searchInterface : interfacesList)
    {
        if (searchInterface != nullptr && searchParameters.searchResName.contains(
                    searchInterface->getPluginInfo()->pluginName))
        {
            if (searchInterface->isPLuginReady())
            {
                completionChecker->addNameOfReadyPlugin(searchInterface->getPluginInfo()->pluginName);
                searchInterface->search(searchParameters);
            }
        }
    }
}

void PluginProcessor::setResultData(QSharedPointer<QList<ResultItem>> currentResultList)
{
    qDebug() << "--> PluginProcessor::setResultData()";
    resultList->append(*currentResultList);
    qDebug() << "All Plugins Search Results Count: " << resultList->size();

    emit addResults(resultList);
    if (completionChecker->check(currentResultList))
    {
        emit pluginsResultFinished();
    }
}
