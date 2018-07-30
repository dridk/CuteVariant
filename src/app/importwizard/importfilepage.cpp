#include "importfilepage.h"

ImportFilePage::ImportFilePage(QWidget *parent)
    :QWizardPage(parent)
{

    setTitle("Select a file to import");
    setSubTitle("Could be raw vcf or annotated vcf with snpEff or Vep");

    QFormLayout * mainLayout = new QFormLayout;

    mFileEdit     = new QLineEdit();
    mBrowseButton = new QPushButton(tr("Browse ..."));
    mUnlockButton = new QPushButton(tr("unlock"));
    mFormatBox    = new QComboBox();

    QHBoxLayout * fileLayout = new QHBoxLayout;
    fileLayout->addWidget(mFileEdit);
    fileLayout->addWidget(mBrowseButton);

    QHBoxLayout * formatLayout = new QHBoxLayout;
    formatLayout->addWidget(mFormatBox);
    formatLayout->addWidget(mUnlockButton);

    mFormatBox->setEnabled(false);

    mainLayout->addRow(tr("Filename"), fileLayout);
    mainLayout->addRow(tr("Format detected"), formatLayout);

    mFormatBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);


    connect(mBrowseButton,&QPushButton::clicked, this, &ImportFilePage::browse);
    connect(mUnlockButton,&QPushButton::clicked, [this](){mFormatBox->setEnabled(true);});

    setLayout(mainLayout);


    registerField("filename", mFileEdit, "text");
    registerField("format", mFormatBox, "currentData");


    // fill combobox

    mFormatBox->clear();



 QMetaEnum metaEnum = QMetaEnum::fromType<cvar::VariantReaderFactory::Format>();

    for (int i=0; i< metaEnum.keyCount();  ++i)
    {
        mFormatBox->addItem(metaEnum.valueToKey(i), metaEnum.value(i));
    }

}

void ImportFilePage::browse()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("Import File"),QDir::homePath());

    if (!filename.isEmpty()){
        mFileEdit->setText(filename);
        detectFormat();

    }



}

void ImportFilePage::detectFormat()
{

    QFile file(mFileEdit->text());
    cvar::VariantReaderFactory::Format format;

    if (cvar::VariantReaderFactory::isGzip(&file))
    {
        auto * gzip = new KCompressionDevice(&file,false, KCompressionDevice::GZip);
        format = cvar::VariantReaderFactory::detectFormat(gzip);
        delete gzip;
    }

    else
        format = cvar::VariantReaderFactory::detectFormat(&file);



    mFormatBox->setCurrentIndex(mFormatBox->findData(format));





}
