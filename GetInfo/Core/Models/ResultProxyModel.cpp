#include "ResultProxyModel.h"
#include "../ResultDisplay.h"

ResultProxyModel::ResultProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

bool ResultProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent)

    switch (source_column)
    {
    case City:
    case Phone:
    case University:
    case Skype:
    case Email:
    case Position:
    case ProfileUrl:
        return false;
    }

    return true;
}
