QT       += core gui
QT       += testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Temporary solution because qt does not support sdk=11.1
macx: CONFIG += sdk_no_version_check
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MAppBaseObj/mappBaseObj.cpp \
    interface/basicForms/mappTable.cpp \
    interface/basicForms/mappTableSettingsForm.cpp \
    interface/basicForms/tableSettingsForm.cpp \
    interface/homeopathy/homeopathyDrugDilutionsSelectForm.cpp \
    interface/homeopathy/homeopathyDrugForm.cpp \
    interface/homeopathy/homeopathyDrugListForm.cpp \
    interface/medicine/medicineDrugBrandSelectForm.cpp \
    interface/medicine/medicineDrugForm.cpp \
    interface/medicine/medicineDrugListForm.cpp \
    interface/medicine/medicineDrugReleaseFormSelectForm.cpp \
    \
    interface/patient/patientForm.cpp \
    interface/patient/patientsListForm.cpp \
    interface/service/serviceForm.cpp \
    interface/service/servicesListForm.cpp \
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
    MAppBaseObj/mappBaseObj.h \
    drugs/homeopathy.h \
    drugs/medicines.h \
    \
    interface/basicForms/mappTable.h \
    interface/basicForms/mappTableSettingsForm.h \
    interface/basicForms/tableSettingsForm.h \
    interface/homeopathy/homeopathyDrugDilutionsSelectForm.h \
    interface/homeopathy/homeopathyDrugForm.h \
    interface/homeopathy/homeopathyDrugListForm.h \
    interface/medicine/medicineDrugBrandSelectForm.h \
    interface/medicine/medicineDrugForm.h \
    interface/medicine/medicineDrugListForm.h \
    interface/medicine/medicineDrugReleaseFormSelectForm.h \
    \
    interface/patient/patientForm.h \
    interface/patient/patientsListForm.h \
    interface/service/serviceForm.h \
    interface/service/servicesListForm.h \
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
    interface/basicForms/mappTable.ui \
    interface/basicForms/mappTableSettingsForm.ui \
    interface/basicForms/tableSettingsForm.ui \
    interface/homeopathy/homeopathyDrugDilutionsSelectForm.ui \
    interface/homeopathy/homeopathyDrugForm.ui \
    interface/homeopathy/homeopathyDrugListForm.ui \
    interface/mainwindow.ui \
    \
    interface/medicine/medicineDrugBrandSelectForm.ui \
    interface/medicine/medicineDrugForm.ui \
    interface/medicine/medicineDrugListForm.ui \
    interface/medicine/medicineDrugReleaseFormSelectForm.ui \
    \
    interface/patient/patientForm.ui \
    interface/patient/patientsListForm.ui \
    \
    interface/service/serviceForm.ui \
    interface/service/servicesListForm.ui \

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
