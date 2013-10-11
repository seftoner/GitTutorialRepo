#include "HistroyProxyModel.h"
#include "DisplayHistoryColumn.h"

HistroyProxyModel::HistroyProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

bool HistroyProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    Q_UNUSED(source_parent)

    if(source_row == 0)
    {
        return false;
    }

    if (!dateFrom.date().isNull())
    {
        QModelIndex index = sourceModel()->index(source_row, HistoryModelData::Date,
                                                 source_parent);
        auto date = sourceModel()->data(index).toDateTime();
        if (!(dateFrom < date))
        {
            return false;
        }
    }

    if (!dateTo.date().isNull())
    {
        QModelIndex index = sourceModel()->index(source_row, HistoryModelData::Date,
                                                 source_parent);
        auto date = sourceModel()->data(index).toDateTime();
        if (dateTo < date)
        {
            return false;
        }
    }

    if (!knowledge.isEmpty()) {
        QModelIndex index = sourceModel()->index(source_row, HistoryModelData::Knowledge);
        if (!sourceModel()->data(index).toString().contains(knowledge))
        {
            return false;
        }
    }

    if (!city.isEmpty()) {
        QModelIndex index = sourceModel()->index(source_row, HistoryModelData::City);
        if (city != sourceModel()->data(index).toString())
        {
            return false;
        }
    }

    if (!resourceName.isEmpty())
    {
        QModelIndex index = sourceModel()->index(source_row, HistoryModelData::ResourceName);
        if (resourceName != sourceModel()->data(index).toString())
        {
            return false;
        }
    }

    if (!country.isEmpty()) {
        QModelIndex index = sourceModel()->index(source_row, HistoryModelData::Country);
        if (country != sourceModel()->data(index).toString())
        {
            return false;
        }
    }

    if (!university.isEmpty()) {
        QModelIndex index = sourceModel()->index(source_row, HistoryModelData::University);
        if (university != sourceModel()->data(index).toString())
        {
            return false;
        }
    }

    return true;
}

QVariant HistroyProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Horizontal)
    {
        return QSortFilterProxyModel::headerData(section, orientation, role);
    }

    return section + 1;
}

void HistroyProxyModel::setKnowledge(const QString &knowledge)
{
    if(this->knowledge != knowledge)
    {
        this->knowledge = knowledge;
        invalidateFilter();
    }
}

void HistroyProxyModel::setCity(const QString &city)
{
    if(this->city != city)
    {
        this->city = city;
        invalidateFilter();
    }
}

void HistroyProxyModel::setCountry(const QString &country)
{
    if(this->country != country)
    {
        this->country = country;
        invalidateFilter();
    }
}

void HistroyProxyModel::setUniversity(const QString &university)
{
    if(this->university != university)
    {
        this->university = university;
        invalidateFilter();
    }
}

void HistroyProxyModel::setDateFrom(const QDateTime &date)
{
    if(dateFrom != date)
    {
        dateFrom = date;
        invalidateFilter();
    }
}

void HistroyProxyModel::setDateTo(const QDateTime &date)
{
    if(dateTo != date)
    {
        dateTo = date;
        invalidateFilter();
    }
}

void HistroyProxyModel::setResourceName(const QString &resourceName)
{
    if(this->resourceName != resourceName)
    {
        this->resourceName = resourceName;
        invalidateFilter();
    }
}

void HistroyProxyModel::clearFilter()
{
    knowledge = "";
    city = "";
    university = "";
    country = "";
    dateFrom.setDate(QDate());
    dateTo.setDate(QDate());
    invalidateFilter();
}
