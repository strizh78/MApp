#include "patientForm.h"
#include "ui_patientForm.h"

#include "interface/appointment/appointmentForm.h"
#include "interface/appointment/appointmentMiniForm.h"

#include "interface/utils.h"

#include <QMessageBox>

namespace {
    QList<QStandardItem*> createInfoRow(const QString& key, const QString& value) {
        QList<QStandardItem*> lst;
        auto* keyItem = new QStandardItem;
        keyItem->setText(key);
        auto* valueItem = new QStandardItem;
        valueItem->setText(value);
        lst << keyItem << valueItem;
        return lst;
    }

    std::vector<QString> getInvalidFields(const Patient& patient) {
        std::vector<QString> wrongFields;
        if (patient.nameInfo().surname.isEmpty() ||
            patient.nameInfo().name.isEmpty())
        {
            wrongFields.push_back("\"ФИО\"");
        }

        if (patient.address().isEmpty()) {
            wrongFields.push_back("\"Адрес\"");
        }

        if (patient.birthDate() > QDate::currentDate()) {
            wrongFields.push_back("\"Дата рождения\"");
        }

        auto keys = patient.additionalInfo().keys();
        for (auto& key : keys) {
            if (key.isEmpty() || patient.additionalInfo()[key].isEmpty()) {
                wrongFields.push_back("\"Дополнительная информация\"");
                break;
            }
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

PatientForm::PatientForm(std::shared_ptr<DatabaseInterface> database,
                         std::optional<Patient> patient,
                         OpenMode mode,
                         QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientForm)
    , infoViewModel_(std::make_shared<QStandardItemModel>())
    , patient_(patient.value_or(Patient()))
    , openMode_(mode)
    , database_(database)
{
    if (patient.has_value() && openMode_ == OpenMode::CREATE) {
        openMode_ = OpenMode::EDIT;
    }

    setupUi();
    setupInfoTable();
    fillFormPatientInfo();
    setupAppointmentsInfo();

    isModified = false;
}

PatientForm::~PatientForm() {
    delete ui;
}

void PatientForm::fieldEdited() {
    isModified = true;
}

void PatientForm::on_solutionBox_accepted() {
    if (trySavePatient()) {
        close();
    }
}

void PatientForm::on_solutionBox_rejected() {
    close();
}

void PatientForm::on_createInfo_clicked() {
    addPatientInfo("", "");

    int rowNumber = infoViewModel_->rowCount() - 1;
    ui->additionalInfo->selectRow(rowNumber);
    ui->additionalInfo->edit(infoViewModel_->index(rowNumber, 0));
}

void PatientForm::on_deleteInfo_clicked() {
    int currentRow = ui->additionalInfo->currentIndex().row();
    infoViewModel_->removeRow(currentRow);

    int rowCount = infoViewModel_->rowCount();
    ui->additionalInfo->selectRow(std::min(rowCount - 1, currentRow));
    ui->additionalInfo->setFocus();

    if (rowCount == 0) {
        enableTableButtons(false);
    }
}

void PatientForm::on_editInfo_clicked() {
    ui->additionalInfo->edit(ui->additionalInfo->currentIndex());
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
        new AppointmentForm(database_, AppointmentForm::CREATE, appointment, this);
    connect(appointmentViewForm, SIGNAL(appointmentCreateSignal(Appointment)),
            this, SLOT(addAppointment(Appointment)));

    showAsWindowModal(appointmentViewForm);
}

void PatientForm::addPatientInfo(const QString& key, const QString& value) {
    infoViewModel_->appendRow(createInfoRow(key, value));
    enableTableButtons(true);
}

void PatientForm::addAppointment(const Appointment& appointment) {
    auto* miniAppointmentForm = new AppointmentMiniForm(appointment, database_, this);
    ui->appointmentsList->insertWidget(2, miniAppointmentForm);

    ui->appointments->setVisible(true);
}

void PatientForm::setupUi() {
    ui->setupUi(this);

    ui->errorLabel->setVisible(false);

    ui->editInfo->setEnabled(false);
    ui->deleteInfo->setEnabled(false);

    setAgeLabelTextColor(palette(), ui->ageDataLabel);
    on_dateEdit_userDateChanged(ui->dateEdit->date());

    connect(ui->nameEdit, SIGNAL(textChanged(QString)), this, SLOT(fieldEdited()));
    connect(ui->dateEdit, SIGNAL(userDateChanged(QDate)), this, SLOT(fieldEdited()));
    connect(ui->addressEdit, SIGNAL(textChanged(QString)), this, SLOT(fieldEdited()));
    connect(ui->createInfo, SIGNAL(clicked()), this, SLOT(fieldEdited()));
    connect(ui->editInfo, SIGNAL(clicked()), this, SLOT(fieldEdited()));
    connect(ui->deleteInfo, SIGNAL(clicked()), this, SLOT(fieldEdited()));

    switch (openMode_) {
    case OpenMode::CREATE:
        setWindowTitle("Создание пациента");
        break;
    case OpenMode::VIEW:
        setEditEnabled(false);
    case OpenMode::EDIT:
        setWindowTitle("Пациент " + patient_.nameInfo().getInitials());
    }
}

void PatientForm::setEditEnabled(bool enabled) {
    ui->nameEdit->setEnabled(enabled);
    ui->dateEdit->setEnabled(enabled);
    ui->addressEdit->setEnabled(enabled);
    ui->additionalInfo->setEnabled(enabled);

    ui->createInfo->setVisible(enabled);
    ui->editInfo->setVisible(enabled);
    ui->deleteInfo->setVisible(enabled);

    ui->solutionBox->clear();
    if (!enabled) {
        ui->solutionBox->addButton(QDialogButtonBox::Close);
    } else {
        ui->solutionBox->addButton(QDialogButtonBox::Cancel);
        ui->solutionBox->addButton(QDialogButtonBox::Save);
    }

    adjustSize();
}

void PatientForm::setupInfoTable() {
    static const QStringList columnNames = {"Ключ", "Значение"};
    infoViewModel_->setHorizontalHeaderLabels(columnNames);

    ui->additionalInfo->setModel(infoViewModel_.get());
    ui->additionalInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void PatientForm::fillFormPatientInfo() {
    if (openMode_ == OpenMode::CREATE) {
        return;
    }

    ui->nameEdit->setText(patient_.nameInfo().getFullName());
    ui->dateEdit->setDate(patient_.birthDate());
    ui->addressEdit->setText(patient_.address());

    const auto& keys = patient_.additionalInfo().keys();
    for (auto& key : keys) {
        addPatientInfo(key, patient_.additionalInfo()[key]);
    }
    if (!keys.empty()) {
        ui->additionalInfo->selectRow(0);
    }
}

void PatientForm::setupAppointmentsInfo() {
    ui->appointments->setHidden(true);

    if (openMode_ == OpenMode::CREATE) {
        return;
    }

    std::vector<Appointment> appointments;
    database_->appointments(appointments);
    std::sort(appointments.begin(), appointments.end(),
              [] (const Appointment& a, const Appointment& b) -> bool {
                  return a.date < b.date;
              });

    for (const auto& x : appointments) {
        if (x.patient == patient_) {
            addAppointment(x);
        }
    }
}

void PatientForm::enableTableButtons(bool enabled) {
    ui->editInfo->setEnabled(enabled);
    ui->deleteInfo->setEnabled(enabled);
}

Patient PatientForm::buildPatientFromFormData() {
    auto splittedName = ui->nameEdit->text().split(' ');

    Patient::NameInfo nameInfo;
    nameInfo.surname = (splittedName.size() >= 1) ? splittedName[0] : "";
    nameInfo.name = (splittedName.size() >= 2) ? splittedName[1] : "";
    nameInfo.patronymic = (splittedName.size() >= 3) ? splittedName[2] : "";

    Patient result(nameInfo,
                   ui->dateEdit->date(),
                   ui->addressEdit->text());
    for (int row = 0; row < infoViewModel_->rowCount(); ++row) {
        auto key =   infoViewModel_->index(row, 0).data().value<QString>();
        auto value = infoViewModel_->index(row, 1).data().value<QString>();
        if (!key.isEmpty() || !value.isEmpty()) {
            result.addAdditionalInfo(key, value);
        }
    }
    return result;
}

bool PatientForm::trySavePatient() {
    Patient patient = buildPatientFromFormData();
    if (!patient.isValid()) {
        ErrorLog::showItemFormWarning(ui->errorLabel, getInvalidFields(patient));
        return false;
    }

    switch (openMode_) {
    case OpenMode::CREATE:
        database_->addPatient(patient);
        emit patientCreateSignal(patient);
        break;
    case OpenMode::EDIT:
        database_->editPatient(patient_, patient);
        emit patientEditSignal(patient);
        break;
    }
    patient_ = patient;
    isModified = false;
    return true;
}
