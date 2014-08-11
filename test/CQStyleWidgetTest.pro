TEMPLATE = app

TARGET = CQStyleWidgetTest

DEPENDPATH += .

QT += widgets

#CONFIG += debug

# Input
SOURCES += \
CQStyleWidgetTest.cpp \

HEADERS += \
CQStyleWidgetTest.h \

DESTDIR     = .
OBJECTS_DIR = .

INCLUDEPATH += \
../include \
.

unix:LIBS += \
-L../lib \
-L../../CQColorPalette/lib \
-L../../CQUtil/lib \
-lCQStyleWidget -lCQColorPalette -lCQUtil
