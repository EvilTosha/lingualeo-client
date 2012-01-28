#-------------------------------------------------
#
# Project created by QtCreator 2012-01-26T11:51:16
#
#-------------------------------------------------

QT       += core gui\
						network

TARGET = lingualeo-client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    comreader.cpp \
    translater.cpp

HEADERS  += mainwindow.h \
    comreader.h \
    translater.h

QMAKE_CXXFLAGS += -std=c++0x
