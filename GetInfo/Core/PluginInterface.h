#ifndef SEARCHINTERFACE_H
#define SEARCHINTERFACE_H

#include "Items/ResultItem.h"
#include "Items/SearchParameters.h"
#include "Items/PluginInfoItem.h"

#include <QList>
#include <QObject>
#include <QWidget>
#include <QSharedPointer>

class PluginInterface : public QObject
{

public:
    virtual ~PluginInterface() {}
    virtual void search(const SearchParameters &parameters) = 0;
    virtual QSharedPointer<PluginInfoItem> getPluginInfo() const = 0;
    virtual bool isPLuginReady() = 0;

signals:
    virtual void endParcing(QSharedPointer<QList<ResultItem> >) = 0;
    virtual void newErrorMessage(const QString& errorMsg) = 0;
    virtual void readyStatusChanged() = 0;
};

Q_DECLARE_INTERFACE(PluginInterface, "GetInfo.PluginInterface")

#endif // SEARCHINTERFACE_H
