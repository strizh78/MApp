#include "interfaceUtils.h"

#include "patient/patient.h"
#include "service/service.h"
#include "drugs/homeopathy.h"
#include "drugs/medicines.h"
#include "appointment/appointment.h"
#include "file/file.h"

#include "interface/basicForms/mappTable.h"

#include "utils/utils.h"

#include <QLayout>
#include <QLayoutItem>
#include <QPainter>

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

    QStandardItem* initials = new QStandardItem(patient.nameInfo.initials);
    initials->setData(getModelData(patient), Qt::UserRole);

    QStandardItem* birthDate = new QStandardItem(patient.birthDate.toString("d MMMM yyyy"));

    QStandardItem* addresses = new QStandardItem(toString(patient.address, "\n"));
    QStandardItem* phones = new QStandardItem(toString(patient.phones, "\n"));
    QStandardItem* emails = new QStandardItem(toString(patient.emails, "\n"));

    lst << initials << birthDate << phones << emails << addresses;
    return lst;
}

QList<QStandardItem*> createServiceRow(const Service& service) {
    QList<QStandardItem*> lst;

    QStandardItem* name = new QStandardItem(service.name);
    name->setData(getModelData(service), Qt::UserRole);
    QStandardItem* price = new QStandardItem(QString::number(service.price));
    QStandardItem* duration = new QStandardItem(service.duration.toString("hч mmм"));

    if (service.isDeprecated) {
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

    QStandardItem* name = new QStandardItem(drug.getFullName());
    name->setData(getModelData(drug), Qt::UserRole);
    QStandardItem* brands = new QStandardItem(drug.getBrands(", "));
    QStandardItem* actSubs = new QStandardItem(drug.getActiveSubstance());
    QStandardItem* price = new QStandardItem(QString::number(drug.price));

    list << name << brands << actSubs << price;

    return list;
}

QList<QStandardItem*> createHomeopathyDrugRow(const homeopathy::Drug& drug) {
    QList<QStandardItem*> lst;

    QStandardItem* name = new QStandardItem(drug.getFullName());
    name->setData(getModelData(drug), Qt::UserRole);
    QStandardItem* group = new QStandardItem(groupToString(drug.group));
    lst << name << group;
    return lst;
}

QList<QStandardItem*> createAppointmentRow(const Appointment& appointment) {
    QList<QStandardItem*> lst;

    QStandardItem* patientName = new QStandardItem(appointment.patient.nameInfo.initials);
    patientName->setData(getModelData(appointment), Qt::UserRole);

    QStandardItem* serviceName = new QStandardItem(appointment.service.name);
    QStandardItem* dateTime = new QStandardItem(appointment.date.toString("d MMMM yyyy, h:mm"));

    QString statusStr = "";
    switch (appointment.getTimeType()) {
    case Appointment::PAST:
        statusStr = appointment.isConducted ? "Приём проведен." : "Приём пропущен.";
        break;
    case Appointment::PRESENT:
        statusStr = appointment.isConducted ? "Приём проведен." : "Сейчас время приёма.";
        break;
    case Appointment::FUTURE:
        statusStr = "Приём запланирован.";
        break;
    }

    QPixmap pix(20, 20);

    QPainter painter(&pix);
    QColor color = getAppointmentColor(appointment);
    painter.setPen(color);
    painter.setBrush(color);
    painter.drawRect(pix.rect());

    QStandardItem* status = new QStandardItem(statusStr);
    status->setIcon(pix);

    lst << patientName << serviceName << dateTime << status;
    return lst;
}
  
QList<QStandardItem*> createFileRow(const File& file) {
    QList<QStandardItem*> lst;

    QStandardItem* name = new QStandardItem(file.name);
    name->setData(getModelData(file), Qt::UserRole);
    lst << name;
    return lst;
}
}

MAppTable* createSelectionForm(QWidget* parent) {
    auto* selectionForm = new MAppTable(parent);

    selectionForm->setFlags(TableFlag::NoBin |
                            TableFlag::SelectionForm);


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

QColor getAppointmentColor(const Appointment& appointment) {
    QColor resultColor;

    switch (appointment.getTimeType()) {
    case Appointment::PAST:
        if (appointment.isConducted) {
            resultColor = {107, 211, 95};
        } else {
            resultColor = {237, 105, 94};
        }
        break;
    case Appointment::PRESENT:
        resultColor = {241, 153, 55};
        if (appointment.isConducted) {
            resultColor = {107, 211, 95};
        }
        break;
    case Appointment::FUTURE:
        resultColor = {153, 158, 248};
        break;
    }

    return resultColor;
}

QFont getFontByParams(QFont baseFont, int pixelSize, QFont::Weight weight, bool isItalic) {
    QFont newFont = baseFont;
    newFont.setPixelSize(pixelSize);
    newFont.setWeight(weight);
    newFont.setItalic(isItalic);

#ifdef Q_OS_WIN
    switch(weight) {
    case QFont::Medium : newFont.setFamily("Montserrat Medium");
        break;
    case QFont::DemiBold : newFont.setFamily("Montserrat SemiBold");
        break;
    case QFont::Light : newFont.setFamily("Montserrat Light");
        break;
    case QFont::Thin : newFont.setFamily("Montserrat Thin");
        break;
    default:
        newFont.setFamily("Montserrat");
    }
#endif

    return newFont;
}

void changeFont(QWidget* widget, int pixelSize, QFont::Weight weight, bool isItalic) {
    widget->setFont(getFontByParams(widget->font(), pixelSize, weight, isItalic));
}
void changeFont(QPainter* painter, int pixelSize, QFont::Weight weight, bool isItalic) {
    painter->setFont(getFontByParams(painter->font(), pixelSize, weight, isItalic));
}

void clearLayout(QLayout *layout) {
    if (layout == nullptr) {
        return;
    }

    QLayoutItem *item;
    while(layout->count() > 0 && (item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}