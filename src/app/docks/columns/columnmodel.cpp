#include "columnmodel.h"

ColumnModel::ColumnModel( QObject *parent)
    :QStandardItemModel(parent)
{

    //load();

    connect(this,SIGNAL(itemChanged(QStandardItem*)),
            this,SLOT(itemCheckChanged(QStandardItem*)));

}

void ColumnModel::load()
{
    qDebug()<<Q_FUNC_INFO<<"load ";
    mFieldItems.clear();
    clear();
    setColumnCount(1);
    for (cvar::Field f : cutevariant->sqliteManager()->fields())
    {
        // create category if not exists
        if (!mCategoriesItems.contains(f.category())){
            mCategoriesItems[f.category()] = createCategory(f.category().toLower());
            mOrderCategories.append(f.category());
        }
        // append item to category
        mCategoriesItems[f.category()]->appendRow(createField(f));
    }

    for (QString key : mOrderCategories)
        appendRow(mCategoriesItems[key]);



    // add Samples
    mSampleItem = createCategory("Samples", "All samples avaibles");

    if (!cutevariant->sqliteManager()->samples().isEmpty())
    {
        for (cvar::Sample s : cutevariant->sqliteManager()->samples())
        {
            QStandardItem * c1 = createCategory(s.name().toUpper());
            mSampleItem->appendRow(c1);

            for (cvar::Field f : cutevariant->sqliteManager()->genotypeFields(s))
            {
                // TODO : check how colname are saved ...
                QStandardItem * g = createField(f);
                c1->appendRow(g);
            }
        }
        appendRow(mSampleItem);
    }
}
//---------------------------------------------------------
QStringList ColumnModel::selectedColumns() const
{
    // get columns variants
    // TODO Make it better, this is useless ....

    QStringList columns;

    for ( auto it : mFieldItems)
    {
        if (it.first->checkState() == Qt::Checked)
        {
            columns.append(it.second.expression());
        }

    }
    return columns;
}
//---------------------------------------------------------
QList<cvar::Field> ColumnModel::selectedFields() const
{
    QList<cvar::Field> fields;
    for (auto it : mFieldItems)
    {
        if (it.first->checkState() == Qt::Checked)
        {
            fields.append(it.second);
        }
    }
    return fields;
}
//---------------------------------------------------------
const cvar::Field ColumnModel::field(const QModelIndex &index) const
{
    QStandardItem * item = itemFromIndex(index);
    if (!item)
        return cvar::Field();


    for (auto it : mFieldItems)
    {
        if (it.first == item)
          return it.second;
    }

    return cvar::Field();

}
//---------------------------------------------------------
void ColumnModel::setCheckBox(bool enabled)
{
        mHasCheckbox = enabled;

}
//---------------------------------------------------------
void ColumnModel::itemCheckChanged(QStandardItem *item)
{
    for (int row = 0; row < item->rowCount(); ++row)
    {
        item->child(row)->setCheckState(item->checkState());
    }

    qDebug()<<selectedColumns();

}
//---------------------------------------------------------
QStandardItem *ColumnModel::createCategory(const QString &name, const QString &description)
{
    QStandardItem * item = new QStandardItem(name);
    item->setToolTip(description);
    item->setCheckable(mHasCheckbox);
    item->setEditable(false);
    return item;
}
//---------------------------------------------------------
QStandardItem *ColumnModel::createField(const cvar::Field &field)
{
    QStandardItem * item = new QStandardItem(field.name());
    item->setToolTip(field.description());
    item->setCheckable(mHasCheckbox);
    item->setEditable(false);
    mFieldItems.append(qMakePair(item,field));
    return item;
}
//---------------------------------------------------------

