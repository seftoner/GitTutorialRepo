#ifndef RESULTPROXYMODEL_H
#define RESULTPROXYMODEL_H

#include <QSortFilterProxyModel>

/*
 * This model hides the following columns:
 * City
 * Phone
 * Skype
 * University
 * Email
 * Position
 * ProfileUrl
 */

class ResultProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ResultProxyModel(QObject *parent = 0);
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
    
signals:
    
public slots:
    
};

#endif // RESULTPROXYMODEL_H
