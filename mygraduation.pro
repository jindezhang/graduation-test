#-------------------------------------------------
#
# Project created by QtCreator 2018-05-07T18:36:47
#
#-------------------------------------------------
QT       += core gui network serialport
QT       +=sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mygraduation
TEMPLATE = app


SOURCES += main.cpp\
    beep.cpp \
    first.cpp \
    json.cpp \
    mybutton.cpp \
    mythread.cpp \
    netmodel.cpp \
    serialmodel.cpp \
    serialmodel_c.cpp \
    sqlmodel.cpp \
    test.cpp \
    top.cpp \
    winbutton.cpp \
    windowadd.cpp \
    windowdownload.cpp \
    windowlog.cpp \
    windowmain.cpp \
    windownet.cpp \
    windowrule.cpp \
    windowselectforid.cpp \
    windowshezhi.cpp \
    windowstart.cpp

HEADERS  += \
    allstruct.h \
    beep.h \
    first.h \
    json.h \
    mybutton.h \
    mythread.h \
    netmodel.h \
    serialmodel.h \
    serialmodel_c.h \
    sqlmodel.h \
    test.h \
    top.h \
    winbutton.h \
    windowadd.h \
    windowdownload.h \
    windowlog.h \
    windowmain.h \
    windownet.h \
    windowrule.h \
    windowselectforid.h \
    windowshezhi.h \
    windowstart.h

FORMS    += mainwindow.ui \
    downloadwindow.ui \
    first.ui \
    netwindow.ui \
    rulewindow.ui \
    selectforid.ui \
    test.ui \
    top.ui \
    winbutton.ui \
    windowadd.ui \
    windowlog.ui \
    windowshezhi.ui \
    windowstart.ui
