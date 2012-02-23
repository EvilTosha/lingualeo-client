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
    translater.h \
    QJson/qjson_export.h \
    QJson/parser.h

QMAKE_CXXFLAGS += -std=c++0x

win32 {
	LIBS += -L./QJson -lqjson0
} macx {
	QMAKE_LFLAGS += -F./QJson
	LIBS += -framework qjson
} unix:!macx {
	LIBS += -L./QJson -lqjson
}

RESOURCES += \
    res.qrc
