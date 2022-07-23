include (appointment/appointment.pri)
include (basicForms/basicForms.pri)
include (file/file.pri)
include (homeopathy/homeopathy.pri)
include (imagePainter/imagePainter.pri)
include (medicine/medicine.pri)
include (patient/patient.pri)
include (service/service.pri)
include (textEditor/textEditor.pri)
include (timetable/timetable.pri)

HEADERS += \
$$PWD/interfaceUtils.h \
$$PWD/mainwindow.h \

SOURCES += \
$$PWD/interfaceUtils.cpp \
$$PWD/mainwindow.cpp \

FORMS += \
$$PWD/mainwindow.ui \

DISTFILES += \
$$PWD/icons/mainIcon.ico \
