#ifndef UNIQMODELCOLUMNCREATOR_H
#define UNIQMODELCOLUMNCREATOR_H

#include <QObject>
#include <QStringList>
#include <QList>
#include "UniqueColumnProxyModel.h"

class QAbstractItemModel;

class UniqHistoryModelColumn : public QObject
{
    Q_OBJECT
public:
    explicit UniqHistoryModelColumn(QObject *parent = 0);
    void setModel(QAbstractItemModel* model);
    QAbstractItemModel* getUniqueData(const int columnIndex);

private:
    QAbstractItemModel* sourceModel;
    mutable QList<UniqueColumnProxyModel> uniqColumnProxyModels;
//    UniqueColumnProxyModel uniqColumnProxyModels;

private:
    void initUniqData();
    
signals:
    void uniqColunsChanged();

public slots:
    
};

#endif // UNIQMODELCOLUMNCREATOR_H
