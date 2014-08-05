TEMPLATE = lib

TARGET = CQStyleWidget

DEPENDPATH += .

QT += widgets

CONFIG += staticlib

# Input
HEADERS += \
../include/CQStyleWidget.h \
../include/CQStyleControl.h \

SOURCES += \
CQStyleWidget.cpp \
CQStyleControl.cpp \

OBJECTS_DIR = ../obj

DESTDIR = ../lib

INCLUDEPATH += \
. \
../include \
../../CQUtil/include \
