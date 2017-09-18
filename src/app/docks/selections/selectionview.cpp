#include "selectionview.h"


SelectionView::SelectionView(QWidget *parent)
    :QTreeWidget(parent)
{
    setEditTriggers(NoEditTriggers);
    setColumnCount(2);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);

//    viewport()->setAutoFillBackground( false );
//    setFrameShape(QFrame::NoFrame);

    setHeaderLabels({"name","count"});

    setWindowTitle("Selection");
    // select first item
   // selectionModel()->select(mModel->index(0,0),QItemSelectionModel::Select);
}
//---------------------------------------------------------------------------------------------

QString SelectionView::tableName() const
{
    if (selectedItems().isEmpty())
        return "";

    return currentItem()->text(0);
}
//---------------------------------------------------------------------------------------------
void SelectionView::load()
{
    clear();
    QTreeWidgetItem * rootItem = new QTreeWidgetItem;
    rootItem->setText(0,"variants");
    rootItem->setText(1, 0);

    for (cvar::VariantSelection selection : cutevariant->sqliteManager()->variantSelections())
    {
        QTreeWidgetItem * item = new QTreeWidgetItem;
        item->setText(0, selection.name());
        item->setText(1,QString::number(selection.count()));
        item->setToolTip(0, selection.description());
        item->setTextAlignment(1,Qt::AlignRight);

        rootItem->addChild(item);
    }

    header()->setSectionResizeMode(0,QHeaderView::Stretch);
    header()->setSectionResizeMode(1,QHeaderView::ResizeToContents);

    addTopLevelItem(rootItem);
    expand(indexFromItem(rootItem));
    setCurrentItem(rootItem);
}
//---------------------------------------------------------------------------------------------
void SelectionView::removeSelection()
{

    for (QTreeWidgetItem * item : selectedItems())
    {
        cutevariant->sqliteManager()->removeSelection(item->text(0));
    }

    load();
}