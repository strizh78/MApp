#include "serviceForm.h"
#include "ui_serviceForm.h"

#include "interface/utils.h"

namespace {
std::vector<QString> getInvalidFields(const Service& service) {
    std::vector<QString> wrongFields;
    if (service.name.isEmpty()) {
        wrongFields.push_back("Наименование");
    }
    if (service.price <= 0) {
        wrongFields.push_back("Цена");
    }
    if (service.duration <= QTime(/*hours*/ 0, /*mins*/ 0)) {
        wrongFields.push_back("Длительность");
    }
    return wrongFields;
}
}

ServiceForm::ServiceForm(std::shared_ptr<DatabaseInterface> database,
                         std::optional<Service> service,
                         QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServiceForm)
    , database_(database)
    , service_(service.value_or(Service()))
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);
    Validators::setDoubleValidator(ui->priceEdit);

    if (service->isExists()) {
        setWindowTitle("Услуга " + service_.name);
    } else {
        setWindowTitle("Создание услуги");
    }

    fillFormServiceInfo();
}

ServiceForm::~ServiceForm() {
    delete ui;
}

void ServiceForm::setEditEnabled(bool enabled) {
    ui->nameEdit->setEnabled(enabled);
    ui->durationEdit->setEnabled(enabled);
    ui->priceEdit->setEnabled(enabled);
    ui->switchActive->setEnabled(enabled);

    ui->solutionBox->clear();
    if (!enabled) {
        ui->solutionBox->addButton(QDialogButtonBox::Close);
    } else {
        ui->solutionBox->addButton(QDialogButtonBox::Cancel);
        ui->solutionBox->addButton(QDialogButtonBox::Save);
    }

    adjustSize();
}


void ServiceForm::fillFormServiceInfo() {
    if (!service_.isExists()) {
        return;
    }

    ui->nameEdit->setText(service_.name);
    ui->durationEdit->setTime(service_.duration);
    ui->priceEdit->setText(QString::number(service_.price));
    ui->switchActive->setChecked(!service_.isDeprecated);
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

    if (service_.isExists()) {
        database_->editService(service_, edited);
        emit serviceEditSignal(edited);
    } else {
        database_->addService(edited);
        emit serviceCreateSignal(edited);
    }
    close();
}

void ServiceForm::on_solutionBox_rejected() {
    close();
}
