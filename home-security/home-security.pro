QT       += core websockets
QT       -= gui

TARGET = home-security
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ping.cpp \
    devicehandler.cpp \
    motionhandler.cpp \
    homesecurity.cpp \
    cameraprocess.cpp \
    storageprocess.cpp \
    websocketserver.cpp

HEADERS += \
    ping.h \
    devicehandler.h \
    motionhandler.h \
    homesecurity.h \
    cameraprocess.h \
    storageprocess.h \
    websocketserver.h

DESTDIR = build
    OBJECTS_DIR = build/.obj
    MOC_DIR = build/.moc
    RCC_DIR = build/.rcc
    UI_DIR = build/.ui

target.path = /usr/sbin
target.extra = su -c "chmod 755 homesecurityd; cp homesecurityd /etc/init.d/; ln -s /etc/init.d/homesecurityd /etc/rc2.d/S01homesecurityd"
target.uninstall = su -c "rm /etc/init.d/homesecurityd; rm /etc/rc2.d/S01homesecurityd"
INSTALLS += target
