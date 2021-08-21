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
                         OpenMode openMode,
                         QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServiceForm)
    , database_(database)
    , service_(service.value_or(Service()))
    , openMode_(openMode)
{
    if (service.has_value() && openMode_ == OpenMode::CREATE) {
        openMode_ = OpenMode::EDIT;
    }

    ui->setupUi(this);
    ui->errorLabel->setVisible(false);
    Validators::setDoubleValidator(ui->priceEdit);

    switch (openMode_) {
        case OpenMode::CREATE:
            setWindowTitle("Создание услуги");
            break;
        case OpenMode::VIEW:
            setEditEnabled(false);
        case OpenMode::EDIT:
            setWindowTitle("Услуга " + service_.name);
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
    if (openMode_ == OpenMode::CREATE) {
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

    switch (openMode_) {
    case OpenMode::CREATE:
        database_->addService(edited);
        emit serviceCreateSignal(edited);
        break;
    case OpenMode::EDIT:
        database_->editService(service_, edited);
        emit serviceEditSignal(edited);
        break;
    }
    close();
}

void ServiceForm::on_solutionBox_rejected() {
    close();
}
