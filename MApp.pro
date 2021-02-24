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
    interface/medicine/medicineDrugBrandSelectForm.cpp \
    interface/medicine/medicineDrugForm.cpp \
    interface/medicine/medicineDrugListForm.cpp \
    interface/medicine/medicineDrugReleaseFormSelectForm.cpp \
    interface/medicine/medicineTableSettingsForm.cpp \
    \
    interface/patient/patientForm.cpp \
    interface/patient/patientsListForm.cpp \
    interface/service/serviceForm.cpp \
    interface/service/servicesListForm.cpp \
    interface/tableSettingsForm.cpp \
    interface/utils.cpp \
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
    \
    contrib/toggleSwitch/switch.cpp \
    \
    tests/patientTests.cpp \
    tests/serviceTests.cpp

HEADERS += \
    drugs/homeopathy.h \
    drugs/medicines.h \
    \
    interface/medicine/medicineDrugBrandSelectForm.h \
    interface/medicine/medicineDrugForm.h \
    interface/medicine/medicineDrugListForm.h \
    interface/medicine/medicineDrugReleaseFormSelectForm.h \
    interface/medicine/medicineTableSettingsForm.h \
    \
    interface/patient/patientForm.h \
    interface/patient/patientsListForm.h \
    interface/service/serviceForm.h \
    interface/service/servicesListForm.h \
    interface/tableSettingsForm.h \
    interface/utils.h \
    patient/patient.h \
    service/service.h \
    \
    database/databaseinterface.h \
    database/databasetest.h \
    \
    interface/mainwindow.h \
    \
    contrib/toggleSwitch/style.h \
    contrib/toggleSwitch/switch.h \
    \
    tests/patientTests.h \
    tests/serviceTests.h

FORMS += \
    interface/mainwindow.ui \
    \
    interface/medicine/medicineDrugBrandSelectForm.ui \
    interface/medicine/medicineDrugForm.ui \
    interface/medicine/medicineDrugListForm.ui \
    interface/medicine/medicineDrugReleaseFormSelectForm.ui \
    interface/medicine/medicineTableSettingsForm.ui \
    \
    interface/patient/patientForm.ui \
    interface/patient/patientsListForm.ui \
    \
    interface/service/serviceForm.ui \
    interface/service/servicesListForm.ui \
    interface/tableSettingsForm.ui

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
