#include "filtermodel.h"
#include <QDebug>


//============================================
FilterModel::FilterModel(QObject * parent)
    :QStandardItemModel(parent)
{
    addLogic(new LogicItem("AND"));
}

void FilterModel::addLogic(LogicItem *item, QStandardItem *parent)
{
    if (parent == nullptr)
        appendRow(item);
    else
        parent->appendRow(item);
}

void FilterModel::addCondition(ConditionalItem *item, QStandardItem *parent)
{
    parent->appendRow(item);
}

QString FilterModel::makeQuery()
{

    QString out = recursiveQuery(item(0,0));

    if (out == "(AND)")
        return QString();

    return out;


}

QString FilterModel::recursiveQuery(QStandardItem *item)
{

    if (item->rowCount() == 0)
        return "("+item->data(ConditionalItem::ConditionRole).toString()+")";

    QStringList list;
    for (int i = 0; i< item->rowCount(); ++i)
    {
        list.append(" "+recursiveQuery(item->child(i))+" ");

    }

    qDebug()<<list;

    QString out ;

    if (item->text() =="AND")
        out = list.join("AND");

    if (item->text() =="OR")
        out = list.join("OR");



    return "("+out+")";


}



