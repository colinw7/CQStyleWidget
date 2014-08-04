TEMPLATE = lib

TARGET = CQStyleWidget

DEPENDPATH += .

QT += widgets

CONFIG += staticlib

# Input
HEADERS += \
../include/CQStyleWidget.h \
../include/CQStyleControl.h \
CQColorChooser.h \
CQFontChooser.h \
CQAlphaButton.h \

SOURCES += \
CQStyleWidget.cpp \
CQStyleControl.cpp \
CQColorChooser.cpp \
CQFontChooser.cpp \
CQAlphaButton.cpp \

OBJECTS_DIR = ../obj

DESTDIR = ../lib

INCLUDEPATH += \
. \
../include \
