#-------------------------------------------------
#
# Project created by QtCreator 2017-09-07T15:34:06
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = keyboard_test_linux
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    keyboardconfig.cpp \
    inputcontroller.cpp \
    inputlistmodel.cpp \
    exception.cpp \
    qwerty_keyboardobserver.cpp \
    functional_keyboardobserver.cpp

HEADERS  += mainwindow.h \
    keyboardobserver.h \
    keyboardconfig.h \
    inputcontroller.h \
    inputlistmodel.h \
    exception.h \
    fkbd_structs.h

FORMS    += mainwindow.ui
