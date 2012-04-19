TEMPLATE = app
QT += network
TARGET = llclient
CONFIG += link_prl

SOURCES += main.cpp\
				mainwindow.cpp \
				comreader.cpp \
				translater.cpp

HEADERS  += mainwindow.h \
				 comreader.h \
				 translater.h \

win32 {
	LIBS += -L../lib -lqjson0
} macx {
	QMAKE_LFLAGS += -F./QJson
	LIBS += -framework qjson
} unix:!macx {
	LIBS += -L./QJson -lqjson
}

INCLUDEPATH += ../QJson

QMAKE_CXXFLAGS += -std=c++0x
