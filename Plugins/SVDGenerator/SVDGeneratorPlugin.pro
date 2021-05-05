# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = VerilogGeneratorPlugin

QT += core xml widgets gui
CONFIG += c++11 release
DEFINES += VERILOGGENERATORPLUGIN_LIB

INCLUDEPATH += ./generatedFiles \
    ./../.. \
    . \
    ./generatedFiles/Debug

LIBS += -L"./../../executable" \
    -lIPXACTmodels

DESTDIR = ../../executable/Plugins

DEPENDPATH += .
MOC_DIR += ./generatedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./generatedFiles
RCC_DIR += ./generatedFiles

include(VerilogGeneratorPlugin.pri)

target.path = $$plugin_path
INSTALLS += target