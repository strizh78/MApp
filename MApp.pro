QT       += core gui
QT       += testlib
QT       += widgets
!win32: !win64: QT       += webenginewidgets
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(database/database.pri)
include(appointment/appointment.pri)
include(interface/interface.pri)
include(MAppBaseObj/MAppBaseObj.pri)
include(contrib/toggleSwitch/toggleSwitch.pri)
include(drugs/drugs.pri)
include(file/file.pri)
include(patient/patient.pri)
include(service/service.pri)
include(timetable/timetable.pri)
include(utils/utils.pri)

SOURCES += \
    main.cpp \

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
    COPY_TO_PATH=$$shell_path($$OUT_PWD/app_fonts)
} else {
    COPY_FROM_PATH=$$PWD/fonts
    COPY_TO_PATH=$$OUT_PWD/app_fonts
}

copydata.commands = $(COPY_DIR) $$COPY_FROM_PATH $$COPY_TO_PATH
first.depends = $(first) copydata

export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

RESOURCES += \
    database/prod/queries.qrc \
    interface/icons.qrc \
    translations.qrc

macx: ICON = interface/icons/mainIcon.png
win32: RC_ICONS = interface/icons/mainIcon.ico

DISTFILES += \
    qtbase_ru.qm \
