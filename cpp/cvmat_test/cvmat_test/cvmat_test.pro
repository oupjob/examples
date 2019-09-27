#-------------------------------------------------
#
# Project created by QtCreator 2017-04-26T19:37:44
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = cvmat_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

#    Release:DESTDIR = ../build-linux/release
#    Debug:DESTDIR = ../build-linux/debug
    INCLUDEPATH += /usr/include/QxtCore
    INCLUDEPATH += /usr/include/QxtGui
#    LIBS+=-L/usr/lib64

    LIBS += -lQxtCore \
            -lQxtGui

    LIBS += -lopencv_core \
            -lopencv_highgui \
            -lopencv_imgcodecs
