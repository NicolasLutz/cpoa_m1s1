
TARGET = vectorMatrix
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../

SOURCES += *.cpp \
    vec2f.cpp \
    vec3f.cpp \
    matrix33f.cpp

HEADERS += *.h *.hpp \
    array.hpp \
    vector.hpp \
    vec2f.h \
    vec3f.h \
    matrix33f.h

DESTDIR = ../lib

QMAKE_CXXFLAGS += -Wall

OTHER_FILES +=

