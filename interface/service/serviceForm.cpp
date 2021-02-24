#include "serviceForm.h"
#include "ui_serviceForm.h"

#include "database/databasetest.h"

#include "interface/utils.h"

namespace {
std::vector<QString> getInvalidFields(const Service& service) {
    std::vector<QString> wrongFields;
    if (service.name().isEmpty()) {
        wrongFields.push_back("Наименование");
    }
    if (service.price() <= 0) {
        wrongFields.push_back("Цена");
    }
    if (service.duration() <= QTime(/*hours*/ 0, /*mins*/ 0)) {
        wrongFields.push_back("Длительность");
    }
    return wrongFields;
}
}

ServiceForm::ServiceForm(std::shared_ptr<DatabaseInterface> database,
                         std::optional<Service> service, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServiceForm)
    , database_(database)
    , service_(service.value_or(Service()))
    , openMode_(service.has_value() ? OpenMode::EDIT : OpenMode::CREATE)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);
    Validators::setDoubleValidator(ui->priceEdit);

    switch (openMode_) {
        case OpenMode::CREATE:
            setWindowTitle("Создание услуги");
            break;
        case OpenMode::EDIT:
            setWindowTitle("Услуга " + service_.name());
    }

    fillFormServiceInfo();
}

ServiceForm::~ServiceForm() {
    delete ui;
}

void ServiceForm::fillFormServiceInfo() {
    if (openMode_ != OpenMode::EDIT) {
        return;
    }

    ui->nameEdit->setText(service_.name());
    ui->durationEdit->setTime(service_.duration());
    ui->priceEdit->setText(QString::number(service_.price()));
    ui->switchActive->setChecked(!service_.isDeprecated());
}

void ServiceForm::on_solutionBox_accepted() {
    Service edited(ui->nameEdit->text(),
                    ui->priceEdit->text().toDouble(),
                    ui->durationEdit->time(),
                    !ui->switchActive->isChecked());
    if (!edited.isValid()) {
        ErrorLog::showItemFormWarning(ui->errorLabel, getInvalidFields(edited));
        return;
    }

    switch (openMode_) {
    case OpenMode::CREATE:
        database_->addService(edited);
        emit serviceCreateSignal(edited);
        break;
    case OpenMode::EDIT:
        database_->editService(service_, edited);
        emit serviceEditSignal(service_, edited);
        break;
    }
    close();
}

void ServiceForm::on_solutionBox_rejected() {
    close();
}
