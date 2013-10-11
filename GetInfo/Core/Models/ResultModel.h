#ifndef RESULTMODEL_H
#define RESULTMODEL_H

#include "../Items/ResultItem.h"
#include <QAbstractTableModel>
#include <QList>
#include <QStringList>
#include "../ResultDisplay.h"

class ResultModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ResultModel(QObject *parent = 0);
    ResultModel(QObject *parent, QList<ResultItem> resultItemsList);

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool removeRows(int row, int count, const QModelIndex &parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void setResultList(const QList<ResultItem> &resultItemsList);

private:
    static const int kColumnCount = 10;
    QList<ResultItem> resultItemsList;
    QStringList headerNames;

private:
    void setupHeader();

signals:

public slots:


};

#endif // RESULTMODEL_H
