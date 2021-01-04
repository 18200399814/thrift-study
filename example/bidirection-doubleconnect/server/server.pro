QT += core

TEMPLATE = app
TARGET = client
CONFIG += console

include ($$PWD/../../../thrift.pri)

HEADERS += ClientHelloService.h \
           communication_constants.h \
           communication_types.h \
           ServerByeService.h

SOURCES += ClientHelloService.cpp \
           communication_constants.cpp \
           communication_types.cpp \
           main.cpp \
           ServerByeService.cpp \
           main.cpp

