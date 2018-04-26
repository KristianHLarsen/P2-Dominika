#-------------------------------------------------
#
# Project created by QtCreator 2014-12-24T17:24:32
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DS18B20_Qt
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    ../../Qt-RGB-LED-master/Serial_RGB_Qt/dialog.cpp \
    ../../Qt-RGB-LED-master/Serial_RGB_Qt/humi.cpp \
    ../../Qt-RGB-LED-master/Serial_RGB_Qt/main.cpp \
    ../../Qt-RGB-LED-master/Serial_RGB_Qt/readwritearduino.cpp \
    ../../Qt-RGB-LED-master/Serial_RGB_Qt/sensor.cpp \
    ../../Qt-RGB-LED-master/Serial_RGB_Qt/temp.cpp

HEADERS  += dialog.h \
    ../../Qt-RGB-LED-master/Serial_RGB_Qt/temp.h \
    ../../Qt-RGB-LED-master/Serial_RGB_Qt/dialog.h \
    ../../Qt-RGB-LED-master/Serial_RGB_Qt/humi_copy.h \
    ../../Qt-RGB-LED-master/Serial_RGB_Qt/temp.h

FORMS    += dialog.ui
