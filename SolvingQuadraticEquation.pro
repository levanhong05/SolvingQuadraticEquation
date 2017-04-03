#-------------------------------------------------
#
# Project created by QtCreator 2017-04-02T21:07:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SolvingQuadraticEquation
TEMPLATE = app

SOURCES +=  main.cpp\
            mainwindow.cpp \
            quadraticequation.cpp

HEADERS  += mainwindow.h \
            quadraticequation.h

FORMS    += mainwindow.ui

RESOURCES += \
            resources.qrc

win32:RC_FILE = SolvingQuadraticEquation.rc
