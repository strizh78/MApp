QT       += core gui
QT       += testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Temporary solution because qt does not support sdk=11.1
macx: CONFIG += sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    interface/medicine/medicineDrugForm.cpp \
    interface/medicine/medicineDrugListForm.cpp \
    main.cpp \
    \
    drugs/homeopathy.cpp \
    drugs/medicines.cpp \
    patient/patient.cpp \
    service/service.cpp \
    \
    database/databaseinterface.cpp \
    database/databasetest.cpp \
    \
    interface/mainwindow.cpp \
    interface/service/serviceEdit.cpp \
    interface/service/servicesList.cpp \
    interface/service/serviceTableSettings.cpp \
    \
    contrib/toggleSwitch/switch.cpp \
    \
    tests/servicetests.cpp

HEADERS += \
    drugs/homeopathy.h \
    drugs/medicines.h \
    interface/medicine/medicineDrugForm.h \
    interface/medicine/medicineDrugListForm.h \
    patient/patient.h \
    service/service.h \
    \
    database/databaseinterface.h \
    database/databasetest.h \
    \
    interface/mainwindow.h \
    interface/service/serviceEdit.h \
    interface/service/servicesList.h \
    interface/service/serviceTableSettings.h \
    \
    contrib/toggleSwitch/style.h \
    contrib/toggleSwitch/switch.h \
    \
    tests/servicetests.h

FORMS += \
    interface/mainwindow.ui \
    \
    interface/medicine/medicineDrugForm.ui \
    interface/medicine/medicineDrugListForm.ui \
    interface/service/serviceEdit.ui \
    interface/service/serviceTableSettings.ui \
    interface/service/servicesList.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    interface/icons.qrc \
    translations.qrc

macx: ICON = interface/icons/mainIcon.png
win32: RC_ICONS = interface/icons/mainIcon.ico

DISTFILES += \
    interface/icons/mainIcon.ico \
    qtbase_ru.qm
