#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T14:27:30
#
#-------------------------------------------------

#QT       += core gui opengl widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testing
TEMPLATE = app

QMAKE_CXXFLAGS += -Wall

INCLUDEPATH += ../vectorMatrix ../image ../csg ../particle ../

LIBS +=  -L ../lib \
#	-lcsg   \
        -limage \
        -lvectorMatrix \
#       -lparticle 

#PRE_TARGETDEPS = ../lib/*

DESTDIR = ../bin

SOURCES += main_test.cpp

HEADERS += main_test.h

# no interface for simple test
#HEADERS  += mainwindow.h
#FORMS    += mainwindow.ui
