#ifndef HISTORYMODEL_H
#define HISTORYMODEL_H

#include <QAbstractTableModel>
#include "../Items/HistoryItem.h"

class HistoryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit HistoryModel(QObject *parent = 0);
    HistoryModel(QObject *parent, QList<HistoryItem>& resultItemsList);

    QVariant data(const QModelIndex& index, int role) const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    bool insertRows(int row, int count, const QModelIndex& parent);
    bool removeRows(int row, int count, const QModelIndex& parent);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;

    void setResultList(const QList<HistoryItem>& resultItemsList);
    void addNewRecord(const HistoryItem& item);

private:
    static const int kColumnCount = 7;
    QList<HistoryItem> resultItemsList;
    QStringList headerNames;

private:
    void setupHeader();
};

#endif // HISTORYMODEL_H
