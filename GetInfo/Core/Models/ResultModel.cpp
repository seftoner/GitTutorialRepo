#include "ResultModel.h"

ResultModel::ResultModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    setupHeader();
}

ResultModel::ResultModel(QObject *parent, QList<ResultItem> list) :
    QAbstractTableModel(parent), resultItemsList(list)
{
    setupHeader();
}

QVariant ResultModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() ||
            index.row() < 0 || index.row() >= resultItemsList.count() ||
            index.column() < 0 || index.column() >= kColumnCount)
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        const auto item = resultItemsList.at(index.row());

        switch (index.column())
        {
        case Name:
            return item.name;
        case Surname:
            return item.surname;
        case Position:
            return item.position;
        case City:
            return item.city;
        case University:
            return item.university;
        case Phone:
            return item.phone;
        case Email:
            return item.email;
        case Skype:
            return item.skype;
        case SearchResourceName:
            return item.searchResourceName;
        case ProfileUrl:
            return item.profileUrl;
        default:
            QVariant();
        }
    }
    return QVariant();
}

bool ResultModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() && role != Qt::EditRole)
    {
        return false;
    }

    auto item = resultItemsList[index.row()];
    switch (index.column())
    {
    case Name:
        item.name = value.toString();
        break;
    case Surname:
        item.surname = value.toString();
        break;
    case Position:
        item.position = value.toString();
        break;
    case City:
        item.city = value.toString();
        break;
    case University:
        item.university = value.toString();
        break;
    case Phone:
        item.phone = value.toString();
        break;
    case Email:
        item.email = value.toString();
        break;
    case Skype:
        item.skype = value.toString();
        break;
    case SearchResourceName:
        item.searchResourceName =  value.toString();
        break;
    }
    emit dataChanged(index, index);
    return true;
}

bool ResultModel::removeRows(int row, int count, const QModelIndex &parent)
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

int ResultModel::rowCount(const QModelIndex &parent) const
{
   return parent.isValid() ? 0 : resultItemsList.size();
}

int ResultModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : kColumnCount;
}

QVariant ResultModel::headerData(int section, Qt::Orientation orientation, int role) const
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

Qt::ItemFlags ResultModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable ;
}

void ResultModel::setResultList(const QList<ResultItem>& resultItemsList)
{
    beginResetModel();
    this->resultItemsList = resultItemsList;
    endResetModel();
}

void ResultModel::setupHeader()
{
    headerNames << tr("Name") << tr("Surname") << tr("Position") << tr("City")
                << tr("University") << tr("Phone") << tr("Email")
                << tr("Skype") << tr("Search resource") << tr("Profile link");
}

