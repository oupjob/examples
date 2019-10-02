#-------------------------------------------------
#
# Project created by QtCreator 2017-01-10T23:11:17
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = parametric_line_equation
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    my_line.cpp

HEADERS += \
    my_line.h

win32 {
    INCLUDEPATH += C:\lib\libqxt\include\QxtWidgets
    LIBS += -LC:\lib\libqxt\lib

    INCLUDEPATH += C:/Qt/opencv2.4.1/install/include
    LIBS += -LC:\Qt\opencv2.4.1\install\x86\mingw\lib

    LIBS += -lQxtCored \
            -lQxtWidgetsd

    LIBS += -lopencv_core2411d \
        -lopencv_highgui2411d
}

