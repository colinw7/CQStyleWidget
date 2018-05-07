TEMPLATE = lib

TARGET = CQStyleWidget

QT += widgets

DEPENDPATH += .

QMAKE_CXXFLAGS += -std=c++14

MOC_DIR = .moc

CONFIG += staticlib

SOURCES += \
CQStyleWidget.cpp \
CQStyleControl.cpp \
CQStyleDivider.cpp \

HEADERS += \
../include/CQStyleWidget.h \
../include/CQStyleControl.h \
../include/CQStyleDivider.h \

OBJECTS_DIR = ../obj

DESTDIR = ../lib

INCLUDEPATH += \
. \
../include \
../../CQColorPalette/include \
../../CQUtil/include \
