QT += core widgets sql
QT += concurrent

DEPENDPATH += . ../lib
INCLUDEPATH += ../lib


SOURCES += \
    main.cpp \
    ui/mainwindow.cpp \
    ui/queryeditor.cpp \
    ui/queryhighlighter.cpp \
    ui/logicmodel.cpp \
    ui/logicview.cpp \
    ui/querybuilderwidget.cpp \
    ui/columnmodel.cpp \
    ui/importdialog.cpp \
    ui/tablemodel.cpp \
    ui/resultsview.cpp \
    ui/resultsmodel.cpp \
    ui/qfonticon.cpp \
    ui/locationlineedit.cpp \
    ui/columnview.cpp





win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lcutevariantcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lcutevariantcore
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lcutevariantcore

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

HEADERS += \
    ui/mainwindow.h \
    ui/queryeditor.h \
    ui/queryhighlighter.h \
    ui/logicmodel.h \
    ui/logicview.h \
    ui/querybuilderwidget.h \
    ui/columnmodel.h \
    ui/importdialog.h \
    ui/tablemodel.h \
    ui/resultsview.h \
    ui/resultsmodel.h \
    ui/qfonticon.h \
    ui/locationlineedit.h \
    ui/columnview.h

RESOURCES += \
    icons/icons.qrc
