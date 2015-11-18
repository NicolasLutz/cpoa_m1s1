
TARGET = csg
TEMPLATE = lib
CONFIG += staticlib

QMAKE_CXXFLAGS += -Wall

INCLUDEPATH += ../vectorMatrix ../image

SOURCES += *.cpp \
    csgnode.cpp \
    csgprimitive.cpp \
    csgoperation.cpp \
    csgdisk.cpp \
    csgregularpolygon.cpp \
    point.cpp \
    csgtree.cpp

HEADERS += *.h \
    csgnode.h \
    csgprimitive.h \
    csgoperation.h \
    csgdisk.h \
    csgregularpolygon.h \
    point.h \
    csgtree.h

DESTDIR = ../lib

