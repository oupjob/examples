TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    sharedptr.cpp \
    shared_ptr.cpp

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    sharedptr.h \
    shared_ptr.h

