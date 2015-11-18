
TARGET = image
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../vectorMatrix

SOURCES += *.cpp \
    image2grey.cpp

HEADERS += *.h *.hpp \
    imgGradient.h \
    image2d.hpp \
    image2grey.h

DESTDIR = ../lib

