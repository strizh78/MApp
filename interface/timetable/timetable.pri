include(calendarWidget/calendarWidget.pri)
include(dailyTimetable/dailyTimetable.pri)
include(event/event.pri)
include(timetableTop/timetableTop.pri)

HEADERS += \
$$PWD/timetableEvent.h \
$$PWD/timetableForm.h \

SOURCES += \
$$PWD/timetableEvent.cpp \
$$PWD/timetableForm.cpp \

FORMS += \
$$PWD/timetableForm.ui
