#include "CountryCityModelGenerator.h"
#include <QSqlQueryModel>
#include <QAbstractItemModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

CountryCityModelGenerator::CountryCityModelGenerator(QObject *parent) :
    QObject(parent), countryModel(new QSqlQueryModel(this)),
    cityModel(new QSqlQueryModel(this)), cityResultCountLimit("10")
{
}

CountryCityModelGenerator::CountryCityModelGenerator(QSqlDatabase* db,
                                                     QObject* parent)
    : dataBase(db), QObject(parent), countryModel(new QSqlQueryModel(this)),
      cityModel(new QSqlQueryModel(this)), cityResultCountLimit("10")
{
    setupCountryModel();
}

void CountryCityModelGenerator::setDataBase(QSqlDatabase* db)
{
    dataBase = db;
    setupCountryModel();
}

QAbstractItemModel* CountryCityModelGenerator::getCountryModel()
{
    return countryModel;
}

QAbstractItemModel*CountryCityModelGenerator::getCityModel()
{
    return cityModel;
}

void CountryCityModelGenerator::updateCityModelByName(const QString& cityTitle)
{
    if (cityTitle.isEmpty() ||  lastCity[0] == cityTitle[0] || cityTitle.size() > 1)
    {
        qDebug() << "Return";
        return;
    }
    lastCity = cityTitle;
    selectedCountryId = getCountryId(currentCountry);

    QString likeQuery ="SELECT title FROM Cities WHERE countryId = '" +
            selectedCountryId + "' AND  title LIKE '" + cityTitle + "%'";

    QFuture<void> future = QtConcurrent::run(this,
                                             &CountryCityModelGenerator::execCityQueryInOtherThread,
                                             likeQuery);
}

void CountryCityModelGenerator::setupCountryModel()
{
    auto likeQuery = QString("SELECT title, id FROM Countries");
    countryModel->setQuery(likeQuery, *dataBase);
    if (countryModel->lastError().isValid())
    {
        qDebug() << countryModel->lastError();
    }
}

void CountryCityModelGenerator::setCurrentCountry(const QString& title)
{
    currentCountry = title;
}

QString CountryCityModelGenerator::getCountryId(const QString& title)
{
    QString query("SELECT id FROM Countries WHERE title = '" + title + "'");
    QSqlQuery countryIdQuery(query, *dataBase);
    if (countryIdQuery.exec())
    {
        countryIdQuery.first();
        return countryIdQuery.value(0).toString();
    }
    return QString();
}

void CountryCityModelGenerator::execCityQueryInOtherThread(const QString& query)
{
    cityModel->setQuery(query, *dataBase);

    if (cityModel->lastError().isValid())
    {
        qDebug() << cityModel->lastError();
    }
}
