#-------------------------------------------------
#
# Project created by QtCreator 2017-08-10T20:07:55
#
#-------------------------------------------------

QT       += core

QT       -= gui

QMAKE_CXXFLAGS += -std=c++11

TARGET = rule_tree
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    rule.cpp \
    test.cpp

HEADERS += \
    rule.h \
    test.h
