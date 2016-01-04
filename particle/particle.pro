
TARGET = particle
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../vectorMatrix ../image

SOURCES += *.cpp \
    particlesystem.cpp \
    particle.cpp \
    _func_particle.cpp

HEADERS += *.h \
    particlesystem.h \
    particle.h \
    _func_particle.h

DESTDIR = ../lib
