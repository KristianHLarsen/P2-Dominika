#-------------------------------------------------
#
# Project created by QtCreator 2015-01-04T01:09:23
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Serial_RGB_Qt
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    readwritearduino.cpp \
    sensor.cpp \
    temp.cpp \
    humi.cpp

HEADERS  += dialog.h \
    readwritearduino.h \
    sensor.h \
    temp.h \
    humi.h

FORMS    += dialog.ui
