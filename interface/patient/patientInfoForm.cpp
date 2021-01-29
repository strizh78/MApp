#include "patientInfoForm.h"
#include "ui_patientInfoForm.h"

#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>

#include "interface/utils.h"

namespace {
bool isValid(QString key, const QString& value) {
    return key.size() != 0 && value.size() != 0;
}

std::vector<QString> getInvalidFields(QString key, const QString& value) {
    std::vector<QString> wrongFields;
    if (key.size() == 0) {
        wrongFields.push_back("\"Ключ\"");
    }
    if (value.size() == 0) {
        wrongFields.push_back("\"Значение\"");
    }
    return wrongFields;
}
}

PatientInfoForm::PatientInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientInfoForm)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);
}

PatientInfoForm::~PatientInfoForm() {
    delete ui;
}

void PatientInfoForm::on_solutionBox_accepted() {
    QString key = ui->keyEdit->text();
    QString value = ui->valueEdit->text();

    if (!isValid(key, value)) {
        ErrorLog::showItemFormWarning(ui->errorLabel, getInvalidFields(key, value));
        return;
    }

    emit signalCreateInfo(key, value);
    close();
}

void PatientInfoForm::on_solutionBox_rejected() {
    close();
}
