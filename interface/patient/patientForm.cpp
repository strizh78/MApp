#include "patientForm.h"
#include "ui_patientForm.h"

#include "database/databasetest.h"

#include <QMessageBox>

#include "interface/utils.h"
#include <iostream>
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
        if (patient.nameInfo().surname.size() == 0 ||
            patient.nameInfo().name.size() == 0)
        {
            wrongFields.push_back("\"ФИО\"");
        }

        if (patient.address().size() == 0) {
            wrongFields.push_back("\"Адрес\"");
        }

        if (patient.birthDate() > QDate::currentDate()) {
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

    int getCurrentAge(QDate birthDate) {
        QDate today = QDate::currentDate();
        int age = today.year() - birthDate.year();
        if (QDate(1, birthDate.month(), birthDate.day()) > QDate(1, today.month(), today.day())) {
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
                         std::optional<Patient> patient, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientForm)
    , infoViewModel_(std::make_shared<QStandardItemModel>())
    , patient_(patient.value_or(Patient()))
    , openMode_(patient.has_value() ? OpenMode::EDIT : OpenMode::CREATE)
    , database_(database)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);
    setAgeLabelTextColor(palette(), ui->ageDataLabel);

    switch (openMode_) {
    case OpenMode::CREATE:
        setWindowTitle("Создание пациента");
        break;
    case OpenMode::EDIT:
        setWindowTitle("Пациент " + patient->nameInfo().getInitials());
    }

    fillFormPatientInfo();

    static const QStringList columnNames = {"Ключ", "Значение"};
    infoViewModel_->setHorizontalHeaderLabels(columnNames);
    ui->additionalInfo->setModel(infoViewModel_.get());
    ui->additionalInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

PatientForm::~PatientForm() {
    delete ui;
}

void PatientForm::fillFormPatientInfo() {
    if (openMode_ != OpenMode::EDIT) {
        return;
    }

    ui->nameEdit->setText(patient_.nameInfo().getFullName());
    ui->dateEdit->setDate(patient_.birthDate());
    ui->addressEdit->setText(patient_.address());

    auto keys = patient_.additionalInfo().keys();
    for (auto& key : keys) {
        addPatientInfo(key, patient_.additionalInfo()[key]);
    }
}

void PatientForm::on_solutionBox_accepted() {
    Patient patient = buildPatientFromFormData();
    if (!patient.isValid()) {
        ErrorLog::showItemFormWarning(ui->errorLabel, getInvalidFields(patient));
        return;
    }

    switch (openMode_) {
    case OpenMode::CREATE:
        database_->addPatient(patient);
        emit patientCreateSignal(patient);
        break;
    case OpenMode::EDIT:
        database_->editPatient(patient_, patient);
        emit patientEditSignal(patient_, patient);
        break;
    }
    close();
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
        auto keyIndex = infoViewModel_->index(row, 0);
        auto keyValue = infoViewModel_->index(row, 1);
        result.addAdditionalInfo(keyIndex.data().value<QString>(),
                                 keyValue.data().value<QString>());
    }
    return result;
}

void PatientForm::on_solutionBox_rejected() {
    close();
}

void PatientForm::addPatientInfo(const QString& key, const QString& value) {
    infoViewModel_->appendRow(createInfoRow(key, value));
}

void PatientForm::on_createInfo_clicked() {
    auto* patientInfoForm = new PatientInfoForm();
    connect(patientInfoForm, SIGNAL(signalCreateInfo(const QString&, const QString&)), this, SLOT(addPatientInfo(const QString&, const QString&)));
    patientInfoForm->setAttribute(Qt::WA_DeleteOnClose, true);
    patientInfoForm->show();
}

void PatientForm::on_deleteInfo_clicked() {
    const auto& selectedRows = ui->additionalInfo->selectionModel()->selectedRows();
    if (!selectedRows.empty()) {
        infoViewModel_->removeRow(selectedRows[0].row());
    }
}

void PatientForm::on_dateEdit_userDateChanged(const QDate &date) {
    int age = getCurrentAge(date);
    ui->ageDataLabel->setText(generateAgeString(age));
}
