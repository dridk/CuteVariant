#include "columnview.h"

ColumnView::ColumnView(QWidget *parent)
    :QTreeView(parent)
{
    mModel       = new ColumnModel();
    mProxyModel  = new QSortFilterProxyModel();

    mProxyModel->setSourceModel(mModel);
    mProxyModel->setRecursiveFilteringEnabled(true); // NEW IN Qt 5.10 ! HOURRA
    mProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    setModel(mProxyModel);
    setWindowTitle(tr("Fields"));
    //iewport()->setAutoFillBackground( false );
    // setFrameShape(QFrame::NoFrame);
    header()->hide();

    //    setStyleSheet(
    //        "QTreeView::indicator:unchecked {image: url(:/uncheck.png);}"
    //        "QTreeView::indicator:checked {image: url(:/check.png);}"
    //      );

    setAlternatingRowColors(true);

    connect(mModel,SIGNAL(itemChanged(QStandardItem*)),this, SIGNAL(itemChanged()));


}

QStringList ColumnView::selectedColumns() const
{
    return mModel->selectedColumns();
}

void ColumnView::load()
{
    mModel->load();
}

void ColumnView::setFilter(const QString &txt)
{
    expandAll();
    mProxyModel->setFilterFixedString(txt);
}


void ColumnView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    QModelIndex index = indexAt(event->pos());
    cvar::Field field = mModel->field(index);

    if (!field.isNull())
    {
        qDebug()<<"hello";

        menu.addAction("show Description", [field](){

            QMessageBox::information(nullptr,field.name(), field.description());

        });


        menu.addAction("add Filter ...", [field,this](){

            FilterDialog dialog;
            dialog.setField(field);
            if (dialog.exec())
            {
                emit filterItemCreated(dialog.createCondition());
            }


        });

        menu.exec(event->globalPos());




    }




}



