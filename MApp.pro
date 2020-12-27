QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Temporary solution because qt does not support sdk=11.1
macx: CONFIG += sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databaseinterface.cpp \
    databasetest.cpp \
    homeopathy.cpp \
    main.cpp \
    mainwindow.cpp \
    medicines.cpp \
    patient.cpp \
    service.cpp

HEADERS += \
    databaseinterface.h \
    databasetest.h \
    homeopathy.h \
    mainwindow.h \
    medicines.h \
    patient.h \
    service.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target