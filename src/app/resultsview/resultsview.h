#ifndef RESULTSVIEW_H
#define RESULTSVIEW_H

#include <QtWidgets>
#include "resulttreemodel.h"
#include "project.h"
#include "variantquery.h"
#include "linklistdialog.h"

class ResultsView : public QWidget
{
    Q_OBJECT
public:
    explicit ResultsView(const QString& name = "variants", QWidget *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

public Q_SLOTS:
    void setQuery(const cvar::VariantQuery& query);


protected Q_SLOTS:
    void pageUp();
    void pageDown();
    void pageFirst();
    void pageLast();
    void setPage(int page);
    void save();
    void exportCsv();
    void showVql();

Q_SIGNALS:
    void tableSaved();

protected:
    void contextMenuEvent(QContextMenuEvent * event);



private:
    QTreeView * mView;
    ResultTreeModel * mModel;
    QToolBar * mTopToolBar;
    QToolBar * mBottomToolBar;
    QLineEdit * mPageBox;
    QLabel * mCountLabel;
    QIntValidator * mPageValidator;
    QString mName = "variants";
    cvar::VariantQuery mQuery;

};

#endif // RESULTSVIEW_H
