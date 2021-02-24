#include "tableSettingsForm.h"
#include "ui_tableSettingsForm.h"

TableSettingsForm::TableSettingsForm(const QStringList& columnNames, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableSettingsForm),
    columnCheckBoxes(columnNames.size())
{
    ui->setupUi(this);

    for (int i = 0; i < columnNames.size(); ++i) {
        columnCheckBoxes[i].setText(columnNames[i]);

        columnCheckBoxes[i].setChecked(true);
        ui->verticalLayout->insertWidget(i + 1, &columnCheckBoxes[i]);
    }
}

TableSettingsForm::~TableSettingsForm() {
    delete ui;
}

void TableSettingsForm::on_tableSettingsSolutionBox_accepted() {
    std::vector<bool> columns(columnCheckBoxes.size());

    for (size_t i = 0; i < columnCheckBoxes.size(); ++i) {
        columns[i] = !columnCheckBoxes[i].isChecked();
    }

    emit signalChangeColumnsDisplay(columns);
    close();
}

void TableSettingsForm::on_tableSettingsSolutionBox_rejected() {
    close();
}
