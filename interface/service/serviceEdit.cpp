#include "serviceEdit.h"
#include "ui_serviceEdit.h"

#include "database/databasetest.h"

ServiceEdit::ServiceEdit(std::shared_ptr<DatabaseInterface> database,
                         std::optional<Service> service, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServiceEdit)
    , database_(database)
    , service_(service.value_or(Service()))
    , editType_(service.has_value() ? EditType::EDIT : EditType::CREATE)
{
    ui->setupUi(this);

    switch (editType_) {
        case EditType::CREATE:
            setWindowTitle("Создание услуги");
            break;
        case EditType::EDIT:
            setWindowTitle("Услуга " + service_.name());
    }

    fillFormServiceInfo();
}

ServiceEdit::~ServiceEdit() {
    delete ui;
}

void ServiceEdit::fillFormServiceInfo() {
    if (editType_ != EditType::EDIT) {
        return;
    }

    ui->nameEdit->setText(service_.name());
    ui->durationEdit->setTime(service_.duration());
    ui->priceEdit->setText(QString::number(service_.price()));
    ui->switchActive->setChecked(!service_.isDeprecated());
}

void ServiceEdit::on_solutionBox_accepted() {
    Service edited(ui->nameEdit->text(),
                    ui->priceEdit->text().toDouble(),
                    ui->durationEdit->time(),
                    !ui->switchActive->isChecked());

    switch (editType_) {
        case EditType::CREATE:
            database_->addService(edited);
            emit serviceCreateSignal(edited);
            break;
        case EditType::EDIT:
            database_->editService(service_, edited);
            emit serviceEditSignal(service_, edited);
            break;
    }
    close();
}

void ServiceEdit::on_solutionBox_rejected() {
    close();
}
