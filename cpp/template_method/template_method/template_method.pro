TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    header.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    header.h

