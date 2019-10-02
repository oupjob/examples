TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    cvinterface.cpp

#INCLUDEPATH += C:/Qt/opencv/install/include

#LIBS += -LC:\Qt\opencv2.4.1\install\x86\mingw\lib
#LIBS +=        -lopencv_core310 \
#               -lopencv_imgcodecs310
#        -lopencv_imgcodecs310\

HEADERS += \
    cvinterface.h
