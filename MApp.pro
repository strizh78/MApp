QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Temporary solution because qt does not support sdk=11.1
macx: CONFIG += sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database/databaseinterface.cpp \
    database/databasetest.cpp \
    drugs/homeopathy.cpp \
    drugs/medicines.cpp \
    interface/mainwindow.cpp \
    main.cpp \
    patient/patient.cpp \
    service/service.cpp

HEADERS += \
    database/databaseinterface.h \
    database/databasetest.h \
    drugs/homeopathy.h \
    drugs/medicines.h \
    interface/mainwindow.h \
    patient/patient.h \
    service/service.h

FORMS += \
    interface/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
