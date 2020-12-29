QMAKE_CFLAGS_DEBUG -= -MDd      #设置运行时库去掉多线程Dll调试版(/MDd)，即MD_DynamicDebug
QMAKE_CXXFLAGS_DEBUG -= -MDd

QMAKE_CFLAGS_DEBUG += -MTd      #在pro中设置运行时库为多线程静态调试版(/MTd)，即MD_StaticDebug
QMAKE_CXXFLAGS_DEBUG += -MTd


INCLUDEPATH += $$PWD/../Boost/boost_1_74_0                      \
               $$PWD/..//Thrift/thrift-0.13.0/lib/cpp/src

LIBS += -L$$PWD/../Boost/boost_1_74_0/x64/Debug/lib -llibboost_system-vc141-mt-gd-x64-1_74     \
        -L$$PWD/../Boost/boost_1_74_0/x64/Debug/lib -llibboost_thread-vc141-mt-gd-x64-1_74     \
        -L$$PWD/../Boost/boost_1_74_0/x64/Debug/lib -llibboost_chrono-vc141-mt-gd-x64-1_74     \
        -L$$PWD/../Boost/boost_1_74_0/x64/Debug/lib -llibboost_date_time-vc141-mt-gd-x64-1_74  \
        -L$$PWD/thrift-0.13.0/lib/cpp/x64/Debug/lib -llibthrift
