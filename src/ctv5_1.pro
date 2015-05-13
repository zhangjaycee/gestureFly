#-------------------------------------------------
#
# Project created by QtCreator 2015-04-29T19:40:51
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ctv5_1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    CompressiveTracker.cpp \
    RunTracker.cpp \
    handFinder.cpp \
    skinTracker.cpp \
    controlStr.cpp \
    strSender.cpp

HEADERS += \
    CompressiveTracker.h \
    handFinder.h \
    skinTracker.h \
    RunTraker.h \
    controlStr.h \
    strSender.h
 INCLUDEPATH += /usr/local/include \
                 /usr/local/include/opencv \
                 /usr/local/include/opencv2

 LIBS += /usr/local/lib/libopencv_highgui.so \
         /usr/local/lib/libopencv_core.so    \
         /usr/local/lib/libopencv_imgproc.so
