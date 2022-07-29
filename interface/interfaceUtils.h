#pragma once

#include "MAppBaseObj/mappBaseObj.h"

#include <QLabel>
#include <QLineEdit>
#include <QStandardItem>
#include <QRegExpValidator>

class Patient;
class Service;
class MAppTable;
class Appointment;
class File;

namespace medicine {
class Drug;
}
namespace homeopathy {
class Drug;
}

namespace ErrorLog {
void showItemFormWarning(QLabel* errorText, const std::vector<QString>& wrongFields);
void showItemFormWarning(QLabel* errorLabel, const QString& errorText);
}

namespace Validators {
const QString PHONE_REGEX = "^(\\s*)?(\\+)?([- _():+]?\\d[- _():+]?){10,14}(\\s*)?$";
const QString EMAIL_REGEX = "^[A-Z0-9a-z._-]{1,}@(\\w+)(\\.(\\w+))(\\.(\\w+))?(\\.(\\w+))?$";

void SetValidator(const QRegExp& regExp, QLineEdit* lineEdit);
void setDoubleValidator(QLineEdit* lineEdit);
void setEnglishValidator(QLineEdit* lineEdit);
}

namespace CreateRows {
QList<QStandardItem*> createPatientRow(const Patient& patient);
QList<QStandardItem*> createServiceRow(const Service& service);
QList<QStandardItem*> createMedicineDrugRow(const medicine::Drug& drug);
QList<QStandardItem*> createHomeopathyDrugRow(const homeopathy::Drug& drug);
QList<QStandardItem*> createAppointmentRow(const Appointment& appointment);
QList<QStandardItem*> createFileRow(const File& file);
}

MAppTable* createSelectionForm(QWidget* parent);

void showAsWindowModal(QWidget* form);

QColor getAppointmentColor(const Appointment& appointment);

template <class T>
QVariant getModelData(const T& item) {
    const MAppBaseObj* base = new T(item);
    return QVariant::fromValue(base);
}

template <class T>
T* getValueFromModelData(const QVariant &variant) {
    return (T*)variant.value<const MAppBaseObj*>();
}

void changeFont(QWidget* widget, int pixelSize, QFont::Weight weight, bool isItalic = false);
void changeFont(QPainter* painter, int pixelSize, QFont::Weight weight, bool isItalic = false);

void clearLayout(QLayout *layout);
