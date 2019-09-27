TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    primarybigfilesort.cpp \
    tools.cpp \
    secondarybigfilesort.cpp

HEADERS += \
    primarybigfilesort.h \
    error_messages.h \
    tools.h \
    secondarybigfilesort.h

QMAKE_CXXFLAGS += -std=c++11
