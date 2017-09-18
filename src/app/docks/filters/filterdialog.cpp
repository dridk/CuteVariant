#include "filterdialog.h"

FilterDialog::FilterDialog(QWidget * parent)
    :QDialog(parent)
{

    mWidget  = new FilterWidget;
    QDialogButtonBox * buttons = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
    resize(400,200);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mWidget);
    mainLayout->addWidget(buttons);

    mWidget->layout()->setContentsMargins(0,0,0,0);

    setLayout(mainLayout);

    connect(buttons,SIGNAL(accepted()),this,SLOT(accept()));
    connect(buttons,SIGNAL(rejected()),this,SLOT(reject()));


}

void FilterDialog::setField(const cvar::Field &field)
{

    mWidget->setField(field);

}

FilterItem *FilterDialog::createFilter() const
{
    return mWidget->filterItem();
}