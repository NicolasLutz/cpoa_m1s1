
TARGET = image
TEMPLATE = lib
CONFIG += staticlib


INCLUDEPATH += ../vectorMatrix

SOURCES += *.cpp \
    image2grey.cpp

HEADERS += *.h *.hpp \
    imgGradient.h \
    image2grey.h \
    image2d.hpp

DESTDIR = ../lib

