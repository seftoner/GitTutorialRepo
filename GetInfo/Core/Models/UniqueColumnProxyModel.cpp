#include "UniqueColumnProxyModel.h"
#include <QDebug>
#include <QStringList>

UniqueColumnProxyModel::UniqueColumnProxyModel(QObject *parent, const int column) :
    QSortFilterProxyModel(parent), column(column)
{
}

void UniqueColumnProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    connect(sourceModel, &QAbstractItemModel::modelReset,
            this, &UniqueColumnProxyModel::clearCache);
    QSortFilterProxyModel::setSourceModel(sourceModel);
}

bool UniqueColumnProxyModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, column,
                                             sourceParent);
    QString text = sourceModel()->data(index).toString();

    if (cache.contains(text))
    {
        return false;
    }

    cache.insert(text);
    return true;
}

void UniqueColumnProxyModel::clearCache()
{
    cache.clear();
}
