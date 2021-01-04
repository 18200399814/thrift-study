QT += core

TEMPLATE = app
TARGET = server
CONFIG += console

include($$PWD/../../../thrift.pri)

HEADERS += HelloBidiService.h \
           helloBidiService_constants.h \
           helloBidiService_types.h

SOURCES += HelloBidiService.cpp \
           helloBidiService_constants.cpp \
           helloBidiService_types.cpp \
           main.cpp
