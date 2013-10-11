#include "KnowledgeModelGenerator.h"
#include <QSqlQueryModel>
#include <QAbstractItemModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

KnowledgeModelGenerator::KnowledgeModelGenerator(QObject *parent) :
    QObject(parent), knowledgeModel(new QSqlQueryModel(this)),
    knowledgeResultCountLimit("10")
{
}

KnowledgeModelGenerator::KnowledgeModelGenerator(QSqlDatabase* db,
                                                     QObject* parent)
    : dataBase(db), QObject(parent),
      knowledgeModel(new QSqlQueryModel(this)),
      knowledgeResultCountLimit("10")
{
}

void KnowledgeModelGenerator::setDataBase(QSqlDatabase* db)
{
    dataBase = db;
}

QAbstractItemModel* KnowledgeModelGenerator::getKnowledgeModel()
{
    return knowledgeModel;
}

void KnowledgeModelGenerator::updateKnowledgeModelByName(const QString& knowledgeTitle)
{
    if (knowledgeTitle.isEmpty() ||  lastKnowledge[0] == knowledgeTitle[0] || knowledgeTitle.size() > 1)
    {
        return;
    }

    lastKnowledge = knowledgeTitle;

    QString likeQuery = "SELECT DISTINCT desiredKnowledge FROM QueryHistory WHERE desiredKnowledge LIKE '"
            + knowledgeTitle + "%'";

    QFuture<void> future = QtConcurrent::run(this,
                                             &KnowledgeModelGenerator::execKnowledgeQueryInOtherThread,
                                             likeQuery);
}

void KnowledgeModelGenerator::execKnowledgeQueryInOtherThread(const QString& query)
{
    knowledgeModel->setQuery(query, *dataBase);

    if (knowledgeModel->lastError().isValid())
    {
        qDebug() << knowledgeModel->lastError();
    }
}

