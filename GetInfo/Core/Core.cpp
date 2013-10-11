#include <QDebug>
#include <QFile>

#include "Core.h"
#include "Models/ResultModel.h"
#include "Models/HistoryModel.h"
#include "Models/HistroyProxyModel.h"
#include "Models/ResultProxyModel.h"
#include "InputValidator.h"
#include "PluginProcessor.h"
#include "DB/DataBaseFactory.h"


Core::Core(QObject *parent) :
    QObject(parent), kPluginDir("../plugins")
{
    qDebug() << "Core Constructor";
}

Core::~Core()
{
    qDebug() << "Core Destructor";
    delete pluginProcessor;
}

void Core::init()
{
    qDebug() << "--> Core::init()";
    inputValidator = QSharedPointer<InputValidator>(new InputValidator());
    mainResultModel = new ResultModel(this);
    hiddenColumnModel = new ResultProxyModel(this);
    hiddenColumnModel->setSourceModel(mainResultModel);
    pluginProcessor = new PluginProcessor(this);
    dbManager = new DataBaseFactory(this);
    dataBase = dbManager->createSqliteDataBase();
    genCountryCity = dataBase->getCountryCityGen();
    genKnowledge = dataBase->getKnowledgeGen();

    historyModel = new HistoryModel(this);
    historyQueryResultModel = new ResultModel(this);
    proxyQueryResultModel = new ResultProxyModel(this);
    proxyQueryResultModel->setSourceModel(historyQueryResultModel);

    createConnections();
}

QList<QSharedPointer<PluginInfoItem> > Core::getPluginList()
{
    return *pluginProcessor->getPluginsList();
}

PluginProcessor* Core::getPluginProcessor()
{
    return this->pluginProcessor;
}

QAbstractItemModel *Core::getQueryHistoryModel()
{
    historyModel->setResultList(dataBase->getQueryHistory());
    return historyModel;
}

QAbstractItemModel *Core::getCountryModel() const
{
    return genCountryCity->getCountryModel();
}

QAbstractItemModel *Core::getCityModel() const
{
    return genCountryCity->getCityModel();
}

QAbstractItemModel *Core::getKnowledgeModel() const
{
    return genKnowledge->getKnowledgeModel();
}

void Core::createConnections()
{
    connect(pluginProcessor, &PluginProcessor::addResults, this, &Core::addResultData);
    connect(pluginProcessor, &PluginProcessor::pluginErrorMessage,
            this, &Core::setPluginErrorMessage);
    connect(pluginProcessor, &PluginProcessor::readyStatusChanged, this,
            &Core::pluginStateChanged);
}

void Core::search(const SearchParameters &parameters)
{
    lastSearchParam = parameters;
    pluginProcessor->search(parameters);
}

void Core::addResultData(QSharedPointer<QList<ResultItem>> resultList)
{
    qDebug() << "--> Core::addResultData()";
    mainResultModel->setResultList(*resultList.data());
    dataBase->addNewHistoryRecord(lastSearchParam, *resultList.data());
    historyModel->addNewRecord(dataBase->getLastHistoryRow());//FIXME double insert when sql query has error
    emit setResultModel(hiddenColumnModel);
}

void Core::getQueryResultModel(const int id)
{
    historyQueryResultModel->setResultList(dataBase->getQueryResults(id));
    if (historyQueryResultModel->rowCount() > 0)
    {
        emit setResultModel(proxyQueryResultModel);
    }
}

void Core::deleteHistoryRow(const int id)
{
    dataBase->deleteHistoryRow(id);
}

void Core::addNewPlugin(const QString &path)
{
    qDebug() << "--> Core::addNewPlugin()";
    QFile::copy(path, kPluginDir);
    //TODO rescan plugins dir

    emit setPluginList(*pluginProcessor->getPluginsList());
}

void Core::setCurrentCountry(const QString& country)
{
    qDebug() << "setCurrentCountry" << country;
    genCountryCity->setCurrentCountry(country);
}


void Core::updateCityModel(const QString& city)
{
    genCountryCity->updateCityModelByName(city);
//    emit cityModelChanged(cityModel);
}

void Core::updateKnowledgeModel(const QString& knowledge)
{
    genKnowledge->updateKnowledgeModelByName(knowledge);
}


void Core::pluginStateChanged()
{
    emit setPluginList(*pluginProcessor->getPluginsList());
}
