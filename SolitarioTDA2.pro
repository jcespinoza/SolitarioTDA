#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T01:20:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SolitarioTDA2
TEMPLATE = app


SOURCES += main.cpp\
        mwindow.cpp \
    cardlabel.cpp \
    listPointer.cpp

HEADERS  += mwindow.h \
    cardlabel.h \
    listPointer.h \
    ../TDA/listpointert.h \
    ../TDA/nodet.h

FORMS    += mwindow.ui

RESOURCES += \
    res.qrc
