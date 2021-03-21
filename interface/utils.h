#pragma once

#include "MAppBaseObj/mappBaseObj.h"

#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QStandardItem>
#include <QRegExpValidator>

#include <vector>
#include <sstream>

class Patient;
class Service;
class MAppTable;

namespace medicine {
class Drug;
}
namespace homeopathy {
class Drug;
}

namespace ErrorLog {
void showItemFormWarning(QLabel* errorText, const std::vector<QString>& wrongFields);
}

QString toString(const std::vector<QString>& src, std::string sep = " ");

template <class T>
QString toString(const std::vector<T>& src, std::string sep = " ") {
    std::ostringstream oss;

    if (!src.empty()) {
        std::copy(src.begin(), src.end() - 1, std::ostream_iterator<T>(oss, sep));
        oss << src.back();
    }
    return QString::fromStdString(oss.str());
}

template <class T>
QVariant getModelData(const T& item) {
    const MAppBaseObj* base = new T(item);
    return QVariant::fromValue(base);
}

template <class T>
T* getValueFromModelData(const QVariant &variant) {
    return (T*)variant.value<const MAppBaseObj*>();
}

namespace Validators {
void SetValidator(const QRegExp& regExp, QLineEdit* lineEdit);
void setDoubleValidator(QLineEdit* lineEdit);
void setEnglishValidator(QLineEdit* lineEdit);
}

namespace CreateRows {
QList<QStandardItem*> createPatientRow(const Patient& patient);
QList<QStandardItem*> createServiceRow(const Service& service);
QList<QStandardItem*> createMedicineDrugRow(const medicine::Drug& drug);
QList<QStandardItem*> createHomeopathyDrugRow(const homeopathy::Drug& drug);
}

MAppTable* createSelectionForm(QWidget* parent);

void showAsWindowModal(QWidget* form);
