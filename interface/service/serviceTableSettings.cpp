#include "serviceTableSettings.h"
#include "ui_serviceTableSettings.h"

ServiceTableSettings::ServiceTableSettings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServiceTableSettings)
{
    ui->setupUi(this);
}

ServiceTableSettings::~ServiceTableSettings() {
    delete ui;
}

void ServiceTableSettings::on_tableSettingsSolutionBox_accepted() {
    std::vector<bool> columns = {!ui->name->isChecked(),
                                 !ui->price->isChecked(),
                                 !ui->duration->isChecked()
                                };
    emit signalChangeColumnsDisplay(columns);
    close();
}

void ServiceTableSettings::on_tableSettingsSolutionBox_rejected() {
    close();
}
