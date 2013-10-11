#include "HistoryModel.h"
#include "DisplayHistoryColumn.h"

HistoryModel::HistoryModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    Q_UNUSED(parent);
    setupHeader();
}

HistoryModel::HistoryModel(QObject *parent, QList<HistoryItem>& resultItemsList) :
    QAbstractTableModel(parent),
    resultItemsList(resultItemsList)
{
    Q_UNUSED(parent);
    setupHeader();
}

QVariant HistoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() ||
            index.row() < 0 || index.row() >= resultItemsList.count() ||
            index.column() < 0 || index.column() >= kColumnCount)
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        const HistoryItem item = resultItemsList.at(index.row());

        switch (index.column())
        {
        case HistoryModelData::Id:
            return item.id;
        case HistoryModelData::Date:
            return item.date;
        case HistoryModelData::Knowledge:
            return item.parameters.knowledge;
        case HistoryModelData::University:
            return item.parameters.univercity;
        case HistoryModelData::City:
            return item.parameters.city;
        case HistoryModelData::Country:
            return item.parameters.country;
        case HistoryModelData::ResourceName:
            return item.parameters.searchResName.join(",");
        default:
            QVariant();
        }
    }
    return QVariant();
}

int HistoryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return resultItemsList.size();
}

int HistoryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return kColumnCount;
}

bool HistoryModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i)
    {
        resultItemsList.insert(row, HistoryItem());
    }
    endInsertRows();
    return true;
}

bool HistoryModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i)
    {
        resultItemsList.removeAt(row);
    }
    endRemoveRows();
    return true;
}

QVariant HistoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headerNames.at(section);
    }
    return QString("%1").arg( section + 1 );
}

Qt::ItemFlags HistoryModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable ;
}

void HistoryModel::setResultList(const QList<HistoryItem> &resultItemsList)
{
    beginResetModel();
    //add empty field. it's required for filtering
    this->resultItemsList.append(HistoryItem());

    this->resultItemsList.append(resultItemsList);
    endResetModel();
}

void HistoryModel::addNewRecord(const HistoryItem &item)
{
//    insertRow(rowCount());
//    resultItemsList.last() = item;
//    QModelIndex topLeft = createIndex(rowCount(), 0);
//    QModelIndex bottomRight = this->createIndex(rowCount(), columnCount());

//    emit dataChanged(topLeft, bottomRight);
    //TODO make better implementation
    beginResetModel();
    this->resultItemsList.append(item);
    endResetModel();
}

void HistoryModel::setupHeader()
{
    headerNames << tr("Id") << tr("Date") << tr("Knowledge") << tr("University")
                << tr("City") << tr("Country") << tr("Resource name");
}
