TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    functions.cpp

include(deployment.pri)
qtcAddDeployment()

LIBS += -lUser32 -lDxva2 -lGdi32 -lDXGI

HEADERS += \
    functions.h

