QT += core

TEMPLATE = app
TARGET = server
CONFIG += console

include($$PWD/../../../thrift.pri)

HEADERS += calculator_constants.h  \
           calculator_types.h  \
           CalculatorService.h

SOURCES += calculator_constants.cpp \
           calculator_types.cpp \
           CalculatorService.cpp \
           main.cpp
