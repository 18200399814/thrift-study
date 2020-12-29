QR += core

TEMPLATE = app
TARGET = server

CONFIG += console
DESTDIR = $$PWD/bin

HEADERS += hello_constants.h   \
           hello_types.h       \
           HelloService.h

SOURCES += hello_constants.cpp  \
           hello_types.cpp      \
           HelloService.cpp     \
           main.cpp

INCLUDEPATH += E:/Github/Boost/boost_1_74_0                      \
               E:/Github/Thrift/thrift-0.13.0/lib/cpp/src

LIBS += -LE:/Github/Boost/boost_1_74_0/x64/Debug/lib                          \
        -LE:/Github/Thrift/thrift-0.13.0/lib/cpp/x64/Debug/lib -llibthrift

QMAKE_CFLAGS_DEBUG -= -MDd      #设置运行时库去掉多线程Dll调试版(/MDd)，即MD_DynamicDebug
QMAKE_CXXFLAGS_DEBUG -= -MDd

QMAKE_CFLAGS_DEBUG += -MTd      #在pro中设置运行时库为多线程静态调试版(/MTd)，即MD_StaticDebug
QMAKE_CXXFLAGS_DEBUG += -MTd
