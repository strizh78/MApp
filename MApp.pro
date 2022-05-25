QT       += core gui
QT       += testlib
!win32: !win64: QT       += webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Temporary solution because qt does not support sdk=11.1
macx: CONFIG += sdk_no_version_check
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appointment/appointment.cpp \
    \
    database/test/databaseTest.cpp \
    \
    database/test/appointmentTestDB.cpp \
    database/test/eventTestDB.cpp \
    database/test/fileTestDB.cpp \
    database/test/homeopathyTestDB.cpp \
    database/test/medicineTestDB.cpp \
    database/test/patientTestDB.cpp \
    database/test/serviceTestDB.cpp \
    \
    drugs/dosage.cpp \
    file/file.cpp \
    interface/appointment/appointmentForm.cpp \
    interface/appointment/appointmentMiniForm.cpp \
    interface/appointment/appointmentRecordForm.cpp \
    interface/appointment/appointmentsListForm.cpp \
    MAppBaseObj/mappBaseObj.cpp \
    interface/basicForms/burgerMenuWidget.cpp \
    interface/basicForms/comboBox.cpp \
    interface/basicForms/components/multiColumnSortFilterProxyModel/multiColumnSortFilterProxyModel.cpp \
    interface/basicForms/mappTable.cpp \
    interface/basicForms/mappTableSettingsForm.cpp \
    interface/basicForms/tableSettingsForm.cpp \
    interface/file/displayWidgets/displayManager.cpp \
    interface/file/displayWidgets/imageViewer.cpp \
    interface/file/displayWidgets/pdfViewer.cpp \
    interface/file/displayWidgets/textViewer.cpp \
    interface/file/displayWidgets/viewerInterface.cpp \
    interface/basicForms/editableList/editableList.cpp \
    interface/file/fileForm.cpp \
    interface/file/filesListForm.cpp \
    interface/homeopathy/homeopathyDrugDilutionsSelectForm.cpp \
    interface/homeopathy/homeopathyDrugForm.cpp \
    interface/homeopathy/homeopathyDrugListForm.cpp \
    interface/imagePainter/imagePainter.cpp \
    interface/imagePainter/imageView.cpp \
    interface/interfaceUtils.cpp \
    interface/medicine/dosageForm.cpp \
    interface/medicine/medicineDrugBrandSelectForm.cpp \
    interface/medicine/medicineDrugForm.cpp \
    interface/medicine/medicineDrugListForm.cpp \
    interface/medicine/medicineDrugReleaseFormSelectForm.cpp \
    \
    interface/patient/patientForm.cpp \
    interface/patient/patientsListForm.cpp \
    interface/service/serviceForm.cpp \
    interface/service/servicesListForm.cpp \
    interface/textEditor/textEditor.cpp \
    interface/timetable/calendarWidget/calendarWidget.cpp \
    interface/timetable/dailyTimetable/dailyTimetable.cpp \
    interface/timetable/dailyTimetable/events/dailyTimetableArchive.cpp \
    interface/timetable/dailyTimetable/events/dailyTimetableEvent.cpp \
    interface/timetable/event/eventForm.cpp \
    interface/timetable/timetableEvent.cpp \
    interface/timetable/timetableForm.cpp \
    interface/timetable/timetableTop/dailyTimeline/dailyTimeline.cpp \
    interface/timetable/timetableTop/dailyTimeline/widgets/dailyTimelineForm.cpp \
    interface/timetable/timetableTop/dailyTimeline/widgets/dailyTimelineLine.cpp \
    interface/timetable/timetableTop/timetableTop.cpp \
    main.cpp \
    \
    drugs/homeopathy.cpp \
    drugs/medicines.cpp \
    patient/patient.cpp \
    service/service.cpp \
    \
    \
    interface/mainwindow.cpp \
    \
    contrib/toggleSwitch/switch.cpp \
    \
    timetable/event.cpp \
    timetable/timetableUtils.cpp \
    utils/utils.cpp

HEADERS += \
    appointment/appointment.h \
    \
    database/databaseInterface.h \
    database/test/databaseTest.h \
    \
    database/test/appointmentTestDB.h \
    database/test/eventTestDB.h \
    database/test/fileTestDB.h \
    database/test/itemTestInterface.h \
    database/test/medicineTestDB.h \
    database/test/patientTestDB.h \
    database/test/serviceTestDB.h \
    database/test/homeopathyTestDB.h \
    \
    \
    database/itemDatabaseInterface.h \
    \
    drugs/dosage.h \
    drugs/homeopathy.h \
    drugs/medicines.h \
    \
    file/file.h \
    interface/appointment/appointmentForm.h \
    interface/appointment/appointmentMiniForm.h \
    interface/appointment/appointmentRecordForm.h \
    interface/appointment/appointmentsListForm.h \
    MAppBaseObj/mappBaseObj.h \
    interface/basicForms/burgerMenuWidget.h \
    interface/basicForms/comboBox.h \
    interface/basicForms/components/multiColumnSortFilterProxyModel/multiColumnSortFilterProxyModel.h \
    interface/basicForms/mappTable.h \
    interface/basicForms/mappTableSettingsForm.h \
    interface/basicForms/tableSettingsForm.h \
    interface/file/displayWidgets/displayManager.h \
    interface/file/displayWidgets/imageViewer.h \
    interface/file/displayWidgets/pdfViewer.h \
    interface/file/displayWidgets/textViewer.h \
    interface/file/displayWidgets/viewerInterface.h \
    interface/basicForms/editableList/editableList.h \
    interface/file/fileForm.h \
    interface/file/filesListForm.h \
    interface/homeopathy/homeopathyDrugDilutionsSelectForm.h \
    interface/homeopathy/homeopathyDrugForm.h \
    interface/homeopathy/homeopathyDrugListForm.h \
    interface/imagePainter/imagePainter.h \
    interface/imagePainter/imageView.h \
    interface/interfaceUtils.h \
    interface/medicine/dosageForm.h \
    interface/medicine/medicineDrugBrandSelectForm.h \
    interface/medicine/medicineDrugForm.h \
    interface/medicine/medicineDrugListForm.h \
    interface/medicine/medicineDrugReleaseFormSelectForm.h \
    \
    interface/patient/patientForm.h \
    interface/patient/patientsListForm.h \
    interface/service/serviceForm.h \
    interface/service/servicesListForm.h \
    interface/textEditor/textEditor.h \
    interface/timetable/calendarWidget/calendarWidget.h \
    interface/timetable/dailyTimetable/dailyTimetable.h \
    interface/timetable/dailyTimetable/events/dailyTimetableArchive.h \
    interface/timetable/dailyTimetable/events/dailyTimetableEvent.h \
    interface/timetable/event/eventForm.h \
    interface/timetable/timetableEvent.h \
    interface/timetable/timetableForm.h \
    interface/timetable/timetableTop/dailyTimeline/dailyTimeline.h \
    interface/timetable/timetableTop/dailyTimeline/widgets/dailyTimelineForm.h \
    interface/timetable/timetableTop/dailyTimeline/widgets/dailyTimelineLine.h \
    interface/timetable/timetableTop/timetableTop.h \
    patient/patient.h \
    service/service.h \
    \
    \
    interface/mainwindow.h \
    \
    contrib/toggleSwitch/style.h \
    contrib/toggleSwitch/switch.h \
    \
    timetable/event.h \
    timetable/timetableUtils.h \
    utils/utils.h

FORMS += \
    interface/appointment/appointmentForm.ui \
    interface/appointment/appointmentMiniForm.ui \
    interface/appointment/appointmentRecordForm.ui \
    interface/appointment/appointmentsListForm.ui \
    interface/basicForms/mappTable.ui \
    interface/basicForms/mappTableSettingsForm.ui \
    interface/basicForms/tableSettingsForm.ui \
    interface/basicForms/editableList/editableList.ui \
    interface/file/fileForm.ui \
    interface/file/filesListForm.ui \
    interface/homeopathy/homeopathyDrugDilutionsSelectForm.ui \
    interface/homeopathy/homeopathyDrugForm.ui \
    interface/homeopathy/homeopathyDrugListForm.ui \
    interface/imagePainter/imagePainter.ui \
    interface/mainwindow.ui \
    \
    interface/medicine/dosageForm.ui \
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
    interface/textEditor/textEditor.ui \
    interface/timetable/event/eventForm.ui \
    interface/timetable/timetableForm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

!win32: !win64 {
    copydata.commands = $(COPY_DIR) $$PWD/contrib/pdf.js $$OUT_PWD
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}

win32 {
    COPY_FROM_PATH=$$shell_path($$PWD/fonts)
    COPY_TO_PATH=$$shell_path($$OUT_PWD/fonts)
} else {
    COPY_FROM_PATH=$$PWD/fonts
    COPY_TO_PATH=$$OUT_PWD/fonts
}

copydata.commands = $(COPY_DIR) $$COPY_FROM_PATH $$COPY_TO_PATH
first.depends = $(first) copydata

export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

RESOURCES += \
    interface/icons.qrc \
    translations.qrc

macx: ICON = interface/icons/mainIcon.png
win32: RC_ICONS = interface/icons/mainIcon.ico

DISTFILES += \
    interface/icons/mainIcon.ico \
    qtbase_ru.qm
