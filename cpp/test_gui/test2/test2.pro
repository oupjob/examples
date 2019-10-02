#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T11:28:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    form.h

FORMS    += mainwindow.ui \
    form.ui

INCLUDEPATH += C:/Qt/opencv2.4.1/install/include

LIBS += -LC:\Qt\opencv2.4.1\install\x86\mingw\lib
LIBS += -lopencv_core2411 \
        -lopencv_highgui2411
