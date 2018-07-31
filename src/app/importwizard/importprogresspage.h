#ifndef IMPORTPROGRESSPAGE_H
#define IMPORTPROGRESSPAGE_H
#include <QWizardPage>
#include <QtWidgets>
#include "cutevariant.h"
#include "variantreaderfactory.h"

class ImportProgressPage : public QWizardPage
{
    Q_OBJECT
public:
    ImportProgressPage(QWidget * parent = nullptr);


    void importFile();


    virtual void initializePage() override;
    virtual bool validatePage() override;
    virtual bool isComplete()  const override;

protected Q_SLOTS:
    void updateStep(int progress, const QString& message);
    void importFinished();

private:
    QProgressBar * mBar;
    QFutureWatcher<bool> mWatcher;

    QPlainTextEdit * mMsgEdit;

    QTabWidget * mTabWidget;
    QPushButton * mStartButton;

    bool mDone = false;


};

#endif // IMPORTPROGRESSPAGE_H