TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ping.cpp \
    devicehandler.cpp \
    motionhandler.cpp \
    homesecurity.cpp \
    cameraprocess.cpp \
    backupprocess.cpp

HEADERS += \
    ping.h \
    devicehandler.h \
    motionhandler.h \
    homesecurity.h \
    cameraprocess.h \
    backupprocess.h
