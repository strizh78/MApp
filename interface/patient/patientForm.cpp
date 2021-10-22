#include "patientForm.h"
#include "ui_patientForm.h"

#include "interface/appointment/appointmentForm.h"
#include "interface/appointment/appointmentMiniForm.h"
#include "interface/basicForms/mappTable.h"

#include "interface/utils.h"

#include <QMessageBox>

namespace {
    std::vector<QString> getInvalidFields(const Patient& patient) {
        std::vector<QString> wrongFields;
        if (patient.nameInfo.surname.isEmpty() ||
            patient.nameInfo.name.isEmpty())
        {
            wrongFields.push_back("\"ФИО\"");
        }

        if (patient.birthDate > QDate::currentDate()) {
            wrongFields.push_back("\"Дата рождения\"");
        }
        return wrongFields;
    }

    void setAgeLabelTextColor(const QPalette& basePalette, QLabel* label) {
        QColor color = basePalette.text().color();
        color.setAlpha(256 * 0.70);
        QPalette palette;
        palette.setColor(QPalette::WindowText, color);

        label->setPalette(palette);
    }

    int getCurrentMonth(QDate birthDate) {
        QDate today = QDate::currentDate();

        int month;
        if (today.year() == birthDate.year()) {
            month = today.month() - birthDate.month();
        } else {
            month = today.month() + 12 - birthDate.month();
        }
        if (QDate(1, today.month(), birthDate.day()) > QDate(1, today.month(), today.day())) {
            month--;
        }

        return month;
    }

    QString generateMonthString(int month) {
        if (month < 0 || month > 12) {
            return "nan";
        }

        QString result = '(' + QString::number(month) + ' ';

        if (month % 10 == 1) {
            result += "месяц";
        } else if (month % 10 >= 2 && month % 10 <= 4) {
            result += "месяца";
        } else {
            result += "месяцев";
        }
        result += ')';

        return result;
    }

    int getCurrentAge(QDate birthDate) {
        QDate today = QDate::currentDate();
        int age = today.year() - birthDate.year();
        if (age > 0 && QDate(1, birthDate.month(), birthDate.day()) > QDate(1, today.month(), today.day())) {
            age--;
        }
        return age;
    }

    QString generateAgeString(int age) {
        if (age < 0 || age > 300) {
            return "nan";
        }

        QString result = '(' + QString::number(age) + ' ';

        if (age % 10 == 1) {
            result += "год";
        } else if (age % 10 >= 2 && age % 10 <= 4) {
            result += "года";
        } else {
            result += "лет";
        }
        result += ')';

        return result;
    }
}

PatientForm::PatientForm(DatabasePtr database,
                         std::optional<Patient> patient,
                         QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientForm)
    , patient_(patient.value_or(Patient()))
    , database_(database)
{
    setupUi();
    fillFormPatientInfo();
    isModified = false;
}

PatientForm::~PatientForm() {
    delete ui;
}

void PatientForm::fieldEdited() {
    isModified = true;
}

void PatientForm::on_saveInfoBox_accepted() {
    if (trySavePatient()) {
        close();
    }
}

void PatientForm::on_saveInfoBox_rejected() {
    close();
}

void PatientForm::on_dateEdit_userDateChanged(const QDate &date) {
    int age = getCurrentAge(date);
    if (age != 0) {
        ui->ageDataLabel->setText(generateAgeString(age));
    } else {
        ui->ageDataLabel->setText(generateMonthString(getCurrentMonth(date)));
    }
}

void PatientForm::on_addAppointmentBtn_clicked() {
    if (isModified) {
        auto buttonClicked = QMessageBox::warning(this,
                                                  "Сохранить изменения?",
                                                  "Требуется сохранить изменения перед созданием приёма. Сохранить?",
                                                  QDialogButtonBox::StandardButton::Save,
                                                  QDialogButtonBox::StandardButton::Cancel);
        if (buttonClicked == QDialogButtonBox::StandardButton::Cancel ||
            !trySavePatient())
        {
            return;
        }
    }

    Appointment appointment;
    appointment.patient = patient_;

    auto* appointmentViewForm =
        new AppointmentForm(database_, appointment, this);
    connect(appointmentViewForm, SIGNAL(appointmentCreateSignal(Appointment)),
            this, SLOT(addAppointment(Appointment)));

    showAsWindowModal(appointmentViewForm);
}

void PatientForm::addAppointment(const Appointment& appointment) {
    auto* miniAppointmentForm = new AppointmentMiniForm(appointment, database_, this);
    ui->appointmentsList->insertWidget(/*after label and line*/ 2, miniAppointmentForm);

    ui->rightPart->setVisible(true);
}

void PatientForm::setupUi() {
    ui->setupUi(this);

    ui->errorLabel->setVisible(false);

    ui->adressesList->setMinimumWidth(ui->nameEdit->width());

    ui->phonesList->setRegExp(QRegExp(Validators::PHONE_REGEX));
    ui->phonesList->setMinimumWidth(150);

    ui->emailsList->setRegExp(QRegExp(Validators::EMAIL_REGEX));
    ui->emailsList->setMinimumWidth(200);

    ui->fileList->setFlags(TableFlag::NoAddButton);

    setAgeLabelTextColor(palette(), ui->ageDataLabel);
    on_dateEdit_userDateChanged(ui->dateEdit->date());

    connect(ui->nameEdit, SIGNAL(textChanged(QString)), this, SLOT(fieldEdited()));
    connect(ui->dateEdit, SIGNAL(userDateChanged(QDate)), this, SLOT(fieldEdited()));

    if (patient_.isExists()) {
        setWindowTitle("Пациент " + patient_.nameInfo.initials);
    } else {
        setWindowTitle("Создание пациента");
    }
}

void PatientForm::fillFormPatientInfo() {
    if (!patient_.isExists()) {
        return;
    }

    ui->nameEdit->setText(patient_.nameInfo.getFullName());
    ui->initialsEdit->setText(patient_.nameInfo.initials);
    ui->dateEdit->setDate(patient_.birthDate);

    ui->adressesList->setDataList(patient_.address);
    ui->phonesList->setDataList(patient_.phones);
    ui->emailsList->setDataList(patient_.emails);

    ui->additionalInfo->setHtml(patient_.additionalInfo);

    setupFilesInfo();
    setupAppointmentsInfo();
    adjustSize();
}

void PatientForm::setupFilesInfo() {
    ui->fileList->setupDatabase(database_);
    ui->fileList->fillTable(patient_);
    ui->fileList->setFlags(TableFlag::NoAddButton);
}

void PatientForm::setupAppointmentsInfo() {
    ui->rightPart->hide();

    if (!patient_.isExists()) {
        return;
    }

    std::vector<Appointment> appointments;
    database_->appointment->list(appointments);
    std::sort(appointments.begin(), appointments.end(),
              [] (const Appointment& a, const Appointment& b) -> bool {
                  return a.date < b.date;
              });

    const int maxAppointmentsCount = 3;
    int currentCount = 0;
    for (const auto& x : appointments) {
        if (x.patient == patient_) {
            addAppointment(x);
            if (++currentCount >= maxAppointmentsCount) {
                break;
            }
        }
    }
}

Patient PatientForm::buildPatientFromFormData() {
    patient_.nameInfo.initials = ui->initialsEdit->text();
    patient_.birthDate = ui->dateEdit->date();

    patient_.address = ui->adressesList->getDataList();
    patient_.phones = ui->phonesList->getDataList();
    patient_.emails = ui->emailsList->getDataList();
    patient_.additionalInfo = ui->additionalInfo->toHtml();
    return patient_;
}

bool PatientForm::trySavePatient() {
    buildPatientFromFormData();
    if (!patient_.isValid()) {
        ErrorLog::showItemFormWarning(ui->errorLabel, getInvalidFields(patient_));
        return false;
    }

    if (patient_.isExists()) {
        database_->patient->update(patient_);
        emit patientEditSignal(patient_);
    } else {
        database_->patient->add(patient_);
        emit patientCreateSignal(patient_);
    }

    isModified = false;
    return true;
}

void PatientForm::on_nameEdit_editingFinished() {
    patient_.nameInfo = Patient::NameInfo(ui->nameEdit->text());
    ui->initialsEdit->setText(patient_.nameInfo.initials);
}
