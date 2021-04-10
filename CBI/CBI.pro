QT += core network

CONFIG += c++11
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lOle32

SOURCES += \
        main.cpp \
        serilization/imagereceiverserilization.cpp \
        thread/athread.cpp \
        udp/asyncudpreceiver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    serilization/imagereceiverserilization.h \
    thread/athread.h \
    udp/asyncudpreceiver.h
