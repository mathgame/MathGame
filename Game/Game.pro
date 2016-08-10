TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += object_with_source
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -Wno-unused-parameter
LIBS += -L/usr/local/lib -lSDL2 -ldl -lpthread
SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    dummy.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bins/debug/libs/release/ -lLibs
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bins/debug/libs/debug/ -lLibs
else:unix: LIBS += -L$$PWD/../bins/debug/libs/ -lLibs

INCLUDEPATH += $$PWD/../Libs
DEPENDPATH += $$PWD/../Libs

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../bins/release/libs/libLibs.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../bins/debug/libs/libLibs.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../bins/release/libs/Libs.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../bins/debug/libs/Libs.lib
else:unix: PRE_TARGETDEPS += $$PWD/../bins/debug/libs/libLibs.a
