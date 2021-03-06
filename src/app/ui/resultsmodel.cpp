#include "resultsmodel.h"
ResultsModel::ResultsModel(core::Project * prj, QObject *parent)
    :QStandardItemModel(parent)
{
    mProject = prj;


}

void ResultsModel::setQuery(const QString &raw)
{
    clear();
    mProject->sqliteManager()->queryBuilder()->setFromRaw(raw);
    load();
}

int ResultsModel::totalVariantCount() const
{
    return mProject->sqliteManager()->variantQueryCount();

}

void ResultsModel::load(int offset, int limit)
{
    clear();

    mProject->sqliteManager()->queryBuilder()->setOffset(offset);
    mProject->sqliteManager()->queryBuilder()->setLimit(limit);


    QSqlQuery query = mProject->sqliteManager()->variantQuery();

    qDebug()<<query.lastError().text();
    qDebug()<<query.lastQuery();

    setColumnCount(query.record().count()-1);

    QStringList header;
    // from 1 to avoid id
    for (int i=1; i<query.record().count(); ++i)
        header.append(query.record().field(i).name());

    setHorizontalHeaderLabels(header);

    while (query.next())
    {
        QList<QStandardItem*> row ;
        // from 1 to avoid id
        for (int i=1; i<query.record().count(); ++i)
        {
            QStandardItem * item = new QStandardItem();
            item->setText(query.record().value(i).toString());
            item->setData(query.record().value(0));
            row.append(item);

            if (i==0){

                item->setCheckable(true);
                item->setEditable(false);

                item->setRowCount(10);

                // add Here sub child
            }
        }

        appendRow(row);
    }
}

