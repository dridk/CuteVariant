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
    clear();
    setColumnCount(1);

    // add common Item
    mVariantItem = createItem("Variants","Based columns");
    mVariantItem->appendRow(createItem(tr("chr"), tr("Chromosome"),"chr"));
    mVariantItem->appendRow(createItem(tr("pos"), tr("genomic position"),"pos"));

    //    mVariantItem->child(0)->setCheckState(Qt::Checked);
    //    mVariantItem->child(0)->setEnabled(false);


    //    mVariantItem->child(1)->setCheckState(Qt::Checked);
    //    mVariantItem->child(1)->setEnabled(false);



    mVariantItem->appendRow(createItem(tr("ref"), tr("reference nucleotid"),"ref"));
    mVariantItem->appendRow(createItem(tr("alt"), tr("alternative nucleotid"),"alt"));
    mVariantItem->appendRow(createItem(tr("qual"), tr("quality score"),"qual"));
    mVariantItem->appendRow(createItem(tr("filter"), tr("filter pass"),"filter"));

    appendRow(mVariantItem);

    // Add extra

    mExtraItem = createItem("Extra", "Automatics fields");
    mExtraItem->appendRow(createItem("igv", "Integrative genomics link","igv"));
    mExtraItem->appendRow(createItem("varsome", "Varsome","varsome"));
    appendRow(mExtraItem);


    // add annotation
    mAnnotationItem = createItem("Annotation","Annotation fields");
    for (cvar::Field f : cutevariant->sqliteManager()->fields())
    {
        QStandardItem * c1 = createItem(f.name(),f.description(),f.colname());
        mAnnotationItem->appendRow(c1);
    }
    appendRow(mAnnotationItem);

    // add Samples
    mSampleItem = createItem("Samples", "fields of samples");

    if (!cutevariant->sqliteManager()->samples().isEmpty())
    {

        for (cvar::Sample s : cutevariant->sqliteManager()->samples())
        {

            QStandardItem * c1 = createItem(s.name(), "Sample name", s.name());
            mSampleItem->appendRow(c1);

            for (cvar::Field f : cutevariant->sqliteManager()->genotypeFields())
            {
                // TODO : check how colname are saved ...
                QStandardItem * g = createItem(f.name(), f.description(),f.name());
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
    QStringList columns;

    for (int i=0; i< mVariantItem->rowCount(); ++i)
    {
        if (mVariantItem->child(i)->checkState() == Qt::Checked)
            columns.append(mVariantItem->child(i)->data().toString());
    }

    for (int i=0; i< mAnnotationItem->rowCount(); ++i)
    {
        if (mAnnotationItem->child(i)->checkState() == Qt::Checked)
            columns.append(mAnnotationItem->child(i)->data().toString());
    }

    for (int i=0; i<mSampleItem->rowCount(); ++i)
    {
        QString sample = mSampleItem->child(i)->data().toString();
        for (int j=0; j < mSampleItem->child(i)->rowCount(); ++j)
        {
            if (mSampleItem->child(i)->child(j)->checkState() == Qt::Checked)
                columns.append(QString("gt_%1.%2").arg(sample).arg(mSampleItem->child(i)->child(j)->data().toString()));
        }
    }


    return columns;



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
QStandardItem *ColumnModel::createItem(const QString &name, const QString &description, const QString &colname)
{
    QStandardItem * item = new QStandardItem(name);
    item->setToolTip(description);
    item->setCheckable(true);
    item->setEditable(false);



    item->setData(colname);


    return item;
}
//---------------------------------------------------------

