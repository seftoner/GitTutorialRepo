#ifndef COUNTRYCITYMODELGENERATOR_H
#define COUNTRYCITYMODELGENERATOR_H

#include <QObject>
#include <QSqlDatabase>

class QAbstractItemModel;
class QSqlQueryModel;

class CountryCityModelGenerator : public QObject
{
    Q_OBJECT
public:
    explicit CountryCityModelGenerator(QObject *parent = 0);
    CountryCityModelGenerator(QSqlDatabase* db,
                                       QObject *parent = 0);

    void setDataBase(QSqlDatabase* db);
    void setCurrentCountry(const QString& title);
    
    QAbstractItemModel* getCountryModel();
    QAbstractItemModel* getCityModel();

public slots:
    void updateCityModelByName(const QString& cityTitle);

private:
    QSqlDatabase* dataBase;
    QSqlQueryModel* countryModel;
    QString selectedCountryId;
    QString lastCity;
    QString currentCountry;
    QSqlQueryModel* cityModel;
    const QString cityResultCountLimit;

private:
    void setupCountryModel();
    QString getCountryId(const QString& title);
    void execCityQueryInOtherThread(const QString& query);

};

#endif // COUNTRYCITYMODELGENERATOR_H
