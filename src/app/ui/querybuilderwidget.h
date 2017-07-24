#ifndef QUERYBUILDERWIDGET_H
#define QUERYBUILDERWIDGET_H
#include <QtWidgets>
#include "project.h"
#include "logicview.h"
#include "columnmodel.h"

class QueryBuilderWidget : public QWidget
{
public:
    QueryBuilderWidget(core::Project * prj, QWidget * parent = nullptr);

protected:
    void addWidget(QWidget * w);
    void toolbarClicked(QAction * action);


private:
    core::Project * mProject;
    QToolBar * mBar;
    QStackedWidget * mStack;
    QHash<QAction*, QWidget*> mWidgets;
    QActionGroup * mActionGroup;

    ColumnModel * mColumnModel;


};

#endif // QUERYBUILDERWIDGET_H