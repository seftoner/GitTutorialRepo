#ifndef HISTROYPROXYMODEL_H
#define HISTROYPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QDateTime>

class HistroyProxyModel : public QSortFilterProxyModel
{
public:
    explicit HistroyProxyModel(QObject* parent);

    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setKnowledge(const QString& knowledge);
    void setCity(const QString& city);
    void setCountry(const QString& country);
    void setUniversity(const QString& university);
    void setDateFrom(const QDateTime& date);
    void setDateTo(const QDateTime& date);
    void setResourceName(const QString& resourceName);
    void clearFilter();

private:
    QString knowledge;
    QString city;
    QString university;
    QString country;
    QString resourceName;
    QDateTime dateFrom;
    QDateTime dateTo;
};

#endif // HISTROYPROXYMODEL_H
