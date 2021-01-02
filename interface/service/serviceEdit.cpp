#include "serviceEdit.h"
#include "ui_serviceEdit.h"

#include "database/databasetest.h"

ServiceEdit::ServiceEdit(std::optional<Service> service, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServiceEdit)
    , service_(service.value_or(Service()))
    , editType_(service.has_value() ? EditType::VIEW : EditType::CREATE)
{
    ui->setupUi(this);

    switch (editType_) {
        case EditType::CREATE:
            setWindowTitle("Создание услуги");
            break;
        case EditType::VIEW:
            setWindowTitle("Услуга" + service_.name());
            ui->solutionBox->removeButton(ui->solutionBox->button(QDialogButtonBox::Save));
    }

    fillFormServiceInfo();
}


ServiceEdit::~ServiceEdit() {
    delete ui;
}

void ServiceEdit::fillFormServiceInfo() {
    if (editType_ != EditType::VIEW) {
        return;
    }

    ui->nameEdit->setText(service_.name());
    ui->nameEdit->setReadOnly(true);

    ui->durationEdit->setTime(service_.duration());
    ui->durationEdit->setFocusPolicy(Qt::NoFocus);
    ui->durationEdit->setReadOnly(true);

    ui->priceEdit->setText(QString::number(service_.price()));
    ui->priceEdit->setReadOnly(true);

    ui->switchActive->setChecked(!service_.isDeprecated());
    ui->switchActive->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->switchActive->setFocusPolicy(Qt::NoFocus);
}

void ServiceEdit::on_solutionBox_accepted() {
    switch (editType_) {
        case EditType::CREATE:
        {
            Service created(ui->nameEdit->text(),
                            ui->priceEdit->text().toDouble(),
                            ui->durationEdit->time(),
                            !ui->switchActive->isChecked());
            DatabaseTest().addService(created);
            emit serviceCreateSignal(created);
            break;
        }
        case EditType::VIEW:
            break;
    }
    close();
}

void ServiceEdit::on_solutionBox_rejected() {
    close();
}
