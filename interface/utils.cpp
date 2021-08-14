#include "utils.h"

#include "patient/patient.h"
#include "service/service.h"
#include "drugs/homeopathy.h"
#include "drugs/medicines.h"
#include "appointment/appointment.h"
#include "file/file.h"
#include "interface/basicForms/mappTable.h"

namespace ErrorLog {
void showItemFormWarning(QLabel* errorText, const std::vector<QString>& wrongFields) {
    if (wrongFields.empty()) {
        return;
    }
    errorText->setVisible(true);
    errorText->setText("Недопустимое значение полей: " + toString(wrongFields, ", "));
}

void showItemFormWarning(QLabel* errorLabel, const QString& errorText) {
    if (errorText.isEmpty()) {
        return;
    }
    errorLabel->show();
    errorLabel->setText(errorText);
}
}

QString toString(const std::vector<QString>& src, std::string sep) {
    QString result;

    for (const auto& x : src) {
        result += x + QString::fromStdString(sep);
    }
    result.resize(result.size() - sep.size());

    return result;
}

namespace Validators {
void SetValidator(const QRegExp& regExp, QLineEdit* lineEdit) {
    QRegExpValidator* regExpValidator = new QRegExpValidator(regExp);
    lineEdit->setValidator(regExpValidator);
}

void setDoubleValidator(QLineEdit* lineEdit) {
    QRegExp regExp("[0-9]*[.]?[0-9]*");
    SetValidator(regExp, lineEdit);
}

void setEnglishValidator(QLineEdit* lineEdit) {
    QRegExp regExp("[a-zA-Z]*");
    SetValidator(regExp, lineEdit);
}
}

namespace CreateRows {
QList<QStandardItem*> createPatientRow(const Patient& patient) {
    QList<QStandardItem*> lst;

    QStandardItem* initials = new QStandardItem(patient.nameInfo.getInitials());
    initials->setData(getModelData(patient), Qt::UserRole);

    QStandardItem* birthDate = new QStandardItem(patient.birthDate.toString("d MMMM yyyy"));
    QStandardItem* address = new QStandardItem(patient.address);

    lst << initials << birthDate << address;
    return lst;
}

QList<QStandardItem*> createServiceRow(const Service& service) {
    QList<QStandardItem*> lst;

    QStandardItem* name = new QStandardItem(service.name());
    name->setData(getModelData(service), Qt::UserRole);
    QStandardItem* price = new QStandardItem(QString::number(service.price()));
    QStandardItem* duration = new QStandardItem(service.duration().toString("hч mmм"));

    if (service.isDeprecated()) {
        QColor color = QWidget().palette().text().color();
        color.setAlpha(256 * 0.20);

        name->setData(QVariant::fromValue(color), Qt::ForegroundRole);
        price->setData(QVariant::fromValue(color), Qt::ForegroundRole);
        duration->setData(QVariant::fromValue(color), Qt::ForegroundRole);
    }

    lst << name << price << duration;
    return lst;
}
QList<QStandardItem*> createMedicineDrugRow(const medicine::Drug& drug) {
    QList<QStandardItem*> list;

    QStandardItem* brands = new QStandardItem(drug.getBrands(", "));
    brands->setData(getModelData(drug), Qt::UserRole);
    QStandardItem* name = new QStandardItem(drug.getFullName());
    QStandardItem* price = new QStandardItem(QString::number(drug.price()));

    list << brands << name << price;

    return list;
}

QList<QStandardItem*> createHomeopathyDrugRow(const homeopathy::Drug& drug) {
    QList<QStandardItem*> lst;

    QStandardItem* name = new QStandardItem(drug.getFullName());
    name->setData(getModelData(drug), Qt::UserRole);
    QStandardItem* group = new QStandardItem(groupToString(drug.group()));
    lst << name << group;
    return lst;
}

QList<QStandardItem*> createAppointmentRow(const Appointment& appointment) {
    QList<QStandardItem*> lst;

    QStandardItem* patientName = new QStandardItem(appointment.patient.nameInfo.getInitials());
    patientName->setData(getModelData(appointment), Qt::UserRole);

    QStandardItem* serviceName = new QStandardItem(appointment.service.name());
    QStandardItem* dateTime = new QStandardItem(appointment.date.toString("d MMMM yyyy, h:mm"));

    lst << patientName << serviceName << dateTime;
    return lst;
}
  
QList<QStandardItem*> createFileRow(const File& file) {
    QList<QStandardItem*> lst;

    QStandardItem* name = new QStandardItem(file.name());
    name->setData(getModelData(file), Qt::UserRole);
    lst << name;
    return lst;
}
}

MAppTable* createSelectionForm(QWidget* parent) {
    auto* selectionForm = new MAppTable(parent);

    selectionForm->setFlag(MAppTable::TableSettings::UseBin, false);
    selectionForm->setFlag(MAppTable::TableSettings::UseButtons, false);
    selectionForm->setFlag(MAppTable::TableSettings::UseSolutionBox, true);


    selectionForm->setWindowFlag(Qt::Window);
    selectionForm->setAttribute(Qt::WA_DeleteOnClose, true);

    selectionForm->setWindowTitle("Выберите ...");
    selectionForm->setWindowModality(Qt::WindowModality::WindowModal);

    return selectionForm;
}

void showAsWindowModal(QWidget* form) {
    form->setWindowModality(Qt::WindowModality::WindowModal);
    form->setWindowFlag(Qt::Window);
    form->setAttribute(Qt::WA_DeleteOnClose, true);
    form->show();
}

