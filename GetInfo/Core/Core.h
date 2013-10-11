#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QSharedPointer>
#include <QLineEdit>
#include <QWidget>

#include "Items/SearchParameters.h"
#include "Items/ResultItem.h"
#include "Items/PluginInfoItem.h"
#include "DB/CountryCityModelGenerator.h"
#include "DB/KnowledgeModelGenerator.h"

class QAbstractItemModel;
class ResultModel;
class InputValidator;
class ResultProxyModel;
class PluginProcessor;
class DataBaseFactory;
class IDataBase;
class HistoryModel;

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = 0);
    ~Core();
    void init();

public:
    QSharedPointer<InputValidator> inputValidator;

private:
    QSharedPointer<CountryCityModelGenerator> genCountryCity;
    QSharedPointer<KnowledgeModelGenerator> genKnowledge;

    ResultModel *mainResultModel;
    ResultProxyModel *hiddenColumnModel;

    ResultProxyModel* proxyQueryResultModel;
    ResultModel* historyQueryResultModel;
    HistoryModel* historyModel;

    PluginProcessor* pluginProcessor;
    DataBaseFactory* dbManager;
    IDataBase* dataBase;
    SearchParameters lastSearchParam;

    const QString kPluginDir;

public:
    QList<QSharedPointer<PluginInfoItem> > getPluginList();
    PluginProcessor* getPluginProcessor();
    QAbstractItemModel * getQueryHistoryModel();

    QAbstractItemModel* getKnowledgeModel() const;
    QAbstractItemModel* getCountryModel() const;
    QAbstractItemModel* getCityModel() const;

private:
    void createConnections();

signals:
    void setResultModel(QAbstractItemModel* model);
    void setQueryHistroyModel(QAbstractItemModel* model);
    void setPluginList(const QList<QSharedPointer<PluginInfoItem> >& list);
    void setPluginErrorMessage(const QString& errorMsg);

public slots:
    void addResultData(QSharedPointer<QList<ResultItem>> resultList);
    void getQueryResultModel(const int id);
    void deleteHistoryRow(const int id);
    void search(const SearchParameters &parameters);
    void addNewPlugin(const QString& path);
    //void validateText(QLineEdit* currentLineEdit);
    void setCurrentCountry(const QString& country);

    void updateCityModel(const QString& city);
    void updateKnowledgeModel(const QString& knowledge);

private slots:
    void pluginStateChanged();
};

#endif // CORE_H
