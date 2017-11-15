TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ping.cpp \
    devicehandler.cpp

HEADERS += \
    ping.h \
    devicehandler.h
