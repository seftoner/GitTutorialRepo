#ifndef RESULTITEM_H
#define RESULTITEM_H

#include <QString>

class ResultItem
{
public:
    ResultItem(){}
    ResultItem(const QString name, const QString surname, const QString position,
               const QString city, const QString university, const QString phone,
               const QString email, const QString skype, const QString profileUrl,
               const  QString searchResourceName, const int dbId) :
        name(name), surname(surname), position(position), city(city),
        university(university), phone(phone), email(email), skype(skype),
        searchResourceName(searchResourceName), profileUrl(profileUrl),
        dbId(dbId){}

public:
    QString name;
    QString surname;
    QString position;
    QString city;
    QString university;
    QString phone;
    QString email;
    QString skype;
    QString searchResourceName;
    QString profileUrl;
    int dbId;
};

#endif // RESULTITEM_H
