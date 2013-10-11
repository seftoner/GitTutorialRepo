#ifndef UNIQUECOLUMNPROXYMODEL_H
#define UNIQUECOLUMNPROXYMODEL_H

#include <QSet>
#include <QSortFilterProxyModel>

class UniqueColumnProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit UniqueColumnProxyModel(QObject *parent = 0, const int column = 0);
    void setSourceModel(QAbstractItemModel *sourceModel);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;


private slots:
    void clearCache();

private:
    const int column;
    mutable QSet<QString> cache;
};

#endif // UNIQUECOLUMNPROXYMODEL_H
