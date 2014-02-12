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

HEADERS  += mwindow.h \
    cardlabel.h \
    ../TDA/listpointert.h \
    ../TDA/nodet.h \
    CardPile.h

FORMS    += mwindow.ui

RESOURCES += \
    res.qrc
