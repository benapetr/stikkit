#-------------------------------------------------
#
# Project created by QtCreator 2014-05-24T19:01:03
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = stikkit
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    syslog.cpp \
    webquery.cpp \
    configuration.cpp \
    terminalparser.cpp

HEADERS += \
    syslog.hpp \
    webquery.hpp \
    configuration.hpp \
    terminalparser.hpp
