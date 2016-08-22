#-------------------------------------------------
#
# Project created by QtCreator 2016-08-08T13:13:59
#
#-------------------------------------------------

QT       -= core gui

TARGET = Libs
TEMPLATE = lib
CONFIG += staticlib
CONFIG += object_with_source
QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -Wl,--unresolved-symbols=report-all
QMAKE_CXXFLAGS += -Wno-unused-parameter

CONFIG(release, debug|release) {
    #This is a release build
} else {
    #This is a debug build
    DEFINES += MG_DEBUG
}

DEFINES += LIBS_LIBRARY

SOURCES += libs.cpp \
    BaseComponents/System/ComponentsFactory.cpp \
    ComponentsMgr/EmptyFactory/System/ComponentsFactory.cpp \
    ComponentsMgr/ComponentsMgr.cpp \
    ComponentsMgr/HashConstructor.cpp \
    ComponentsMgr/IBaseComponent.cpp \
    ComponentsMgr/IBaseComponentBasicReaders.cpp \
    ComponentsMgr/IBaseComponentBasicWriters.cpp \
    ComponentsMgr/IBaseComponentHashes.cpp \
    Events/System/ComponentsFactory.cpp \
    FunctionBinder/FunctionBinder/FunctionBinder.cpp \
    FunctionBinder/FunctionCaller/FunctionCaller.cpp \
    FunctionBinder/FunctionConnector/RemoteFunctionConnector.cpp \
    FunctionBinder/FunctionConnector/SimpleFunctionConnector.cpp \
    MsgMgr/MsgMgr.cpp \
    pugixml/pugixml.cpp \
    Tools/Crc.cpp \
    UniStream/iUniStream.cpp \
    UniStream/iUniStreamOperators.cpp \
    UniStream/iUniStreamSTL.cpp \
    UniStream/oUniStream.cpp \
    UniStream/oUniStreamOperators.cpp \
    UniStream/oUniStreamSTL.cpp \
    UniStream/UniStreamTests.cpp \
    XmlParsers/XmlTools.cpp \
    Interpolations/InterpolationBase.cpp \
    Tools/Timer.cpp \
    Tools/Vector2d.cpp \
    PathIterators/Bezier.cpp

HEADERS += libs.h\
        libs_global.h \
    BaseComponents/Settings/ComponentsList.h \
    BaseComponents/Settings/Defines.h \
    BaseComponents/Settings/Includes.h \
    BaseComponents/System/ComponentsFactory.h \
    BaseComponents/System/pop_warning_level.h \
    BaseComponents/System/push_warning_level.h \
    BaseComponents/System/stop_unused_var_warning.h \
    BaseComponents/DummyComponent.h \
    ComponentsMgr/EmptyFactory/Settings/ComponentsList.h \
    ComponentsMgr/EmptyFactory/Settings/Defines.h \
    ComponentsMgr/EmptyFactory/Settings/Includes.h \
    ComponentsMgr/EmptyFactory/System/ComponentsFactory.h \
    ComponentsMgr/EmptyFactory/System/pop_warning_level.h \
    ComponentsMgr/EmptyFactory/System/push_warning_level.h \
    ComponentsMgr/EmptyFactory/System/stop_unused_var_warning.h \
    ComponentsMgr/ComponentMacroEngine.h \
    ComponentsMgr/ComponentsMgr.h \
    ComponentsMgr/ComponentsMgr.hpp \
    ComponentsMgr/ComponentsMgrFwd.h \
    ComponentsMgr/FactoryIncludes.h \
    ComponentsMgr/HashConstructor.h \
    ComponentsMgr/IBaseComponent.h \
    ComponentsMgr/IBaseComponent.hpp \
    ComponentsMgr/IBaseComponentBasicReaders.hpp \
    ComponentsMgr/IBaseComponentBasicWriters.hpp \
    ComponentsMgr/IBaseComponentHashes.hpp \
    Events/Settings/ComponentsList.h \
    Events/Settings/Defines.h \
    Events/Settings/Includes.h \
    Events/System/ComponentsFactory.h \
    Events/System/pop_warning_level.h \
    Events/System/push_warning_level.h \
    Events/System/stop_unused_var_warning.h \
    Events/AllEvents.h \
    Events/DummyEventComponent.h \
    Events/FirstEventComponent.h \
    FunctionBinder/FunctionBinder/FunctionBinder.h \
    FunctionBinder/FunctionBinder/FunctionBinder.hpp \
    FunctionBinder/FunctionBinder/FunctionBinderFunctors.hpp \
    FunctionBinder/FunctionBinder/FunctionBinderStaticFunctors.hpp \
    FunctionBinder/FunctionCaller/FunctionCaller.h \
    FunctionBinder/FunctionCaller/FunctionCaller.hpp \
    FunctionBinder/FunctionConnector/FunctionConnector.h \
    FunctionBinder/FunctionConnector/RemoteFunctionConnector.h \
    FunctionBinder/FunctionConnector/SimpleFunctionConnector.h \
    MsgMgr/MsgMgr.h \
    pugixml/pugiconfig.hpp \
    pugixml/pugixml.hpp \
    Tools/Crc.h \
    UniStream/ioUniStream.h \
    UniStream/iUniStream.h \
    UniStream/iUniStreamSTL.hpp \
    UniStream/oUniStream.h \
    UniStream/oUniStreamSTL.hpp \
    UniStream/UniStream.h \
    UniStream/UniStreamConfig.h \
    UniStream/UniStreamTestUtils.h \
    XmlParsers/XmlTools.h \
    Tools/DebugTools.h \
    Interpolations/InterpolationBase.h \
    BaseComponents/System/empty_comp_cpp \
    BaseComponents/System/empty_comp_h \
    ComponentsMgr/EmptyFactory/System/empty_comp_cpp \
    ComponentsMgr/EmptyFactory/System/empty_comp_h \
    Events/System/empty_comp_cpp \
    Events/System/empty_comp_h \
    Tools/Timer.h \
    Tools/Vector2d.h \
    PathIterators/Bezier.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    Libs.pro.user.3.3-pre1 \
    UniStream/MakeUnitTests \
    ComponentsMgr/CMakeLists.txt \
    Tools/CMakeLists.txt \
    BaseComponents/create_component.py \
    ComponentsMgr/EmptyFactory/create_component.py \
    Events/create_component.py
