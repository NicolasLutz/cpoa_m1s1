
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
    csgtree.cpp \
    _func.cpp \
    boundingbox.cpp

HEADERS += *.h \
    csgnode.h \
    csgprimitive.h \
    csgoperation.h \
    csgdisk.h \
    csgregularpolygon.h \
    csgtree.h \
    _func.h \
    boundingbox.h

DESTDIR = ../lib

