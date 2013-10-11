#ifndef KNOWLEDGEMODELGENERATOR_H
#define KNOWLEDGEMODELGENERATOR_H

#include <QObject>
#include <QSqlDatabase>

class QAbstractItemModel;
class QSqlQueryModel;

class KnowledgeModelGenerator : public QObject
{
    Q_OBJECT
public:
    explicit KnowledgeModelGenerator(QObject *parent = 0);
    KnowledgeModelGenerator(QSqlDatabase* db,
                                       QObject *parent = 0);

    void setDataBase(QSqlDatabase* db);

    QAbstractItemModel* getKnowledgeModel();

public slots:
    void updateKnowledgeModelByName(const QString& cityTitle);

private:
    QSqlDatabase* dataBase;
    QString lastKnowledge;
    QSqlQueryModel* knowledgeModel;
    const QString knowledgeResultCountLimit;

private:
    void execKnowledgeQueryInOtherThread(const QString& query);
};

#endif // KNOWLEDGEMODELGENERATOR_H
