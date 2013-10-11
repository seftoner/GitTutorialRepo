#ifndef SEARCHPARAMETERS_H
#define SEARCHPARAMETERS_H

#include <QString>
#include <QStringList>

class SearchParameters
{
public:
    SearchParameters(){}
    SearchParameters(const QString univercity, const QString knowledge,
                     const QString city, const QString country,
                     const QStringList searchResName = QStringList()) :
        univercity(univercity), knowledge(knowledge), city(city),
        country(country), searchResName(searchResName) {}

public:
    QString univercity;
    QString knowledge;
    QString city;
    QString country;
    QStringList searchResName;
};

#endif // SEARCHPARAMETERS_H
