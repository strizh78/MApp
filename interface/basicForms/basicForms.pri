include(components/multiColumnSortFilterProxyModel/multiColumnSortFilterProxyModel.pri)
include(editableList/editableList.pri)

HEADERS += \
$$PWD/burgerMenuWidget.h \
$$PWD/comboBox.h \
$$PWD/mappTable.h \
$$PWD/mappTableSettingsForm.h \
$$PWD/tableSettingsForm.h \

SOURCES += \
$$PWD/burgerMenuWidget.cpp \
$$PWD/comboBox.cpp \
$$PWD/mappTable.cpp \
$$PWD/mappTableSettingsForm.cpp \
$$PWD/tableSettingsForm.cpp \

FORMS += \
$$PWD/mappTable.ui \
$$PWD/mappTableSettingsForm.ui \
$$PWD/tableSettingsForm.ui \
