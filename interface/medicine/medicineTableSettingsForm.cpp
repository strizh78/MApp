#include "medicineTableSettingsForm.h"
#include "ui_medicineTableSettingsForm.h"

#include <QCheckBox>
#include <QHeaderView>

MedicineTableSettingsForm::MedicineTableSettingsForm(QTableView* table,
                                                     QWidget* parent) :
    QDialog(parent),
    ui(new Ui::MedicineTableSettingsForm),
    table_(table)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    ui->verticalLayout_2->setAlignment(Qt::AlignTop);
    auto* tableModel = table_->model();

    for (int i = 0; i < tableModel->columnCount(); ++i) {
        auto checkBox = new QCheckBox(tableModel->headerData(i, Qt::Horizontal).toString());
        checkBox->setObjectName("checkBox_" + QString::number(i));
        checkBox->setChecked(!table_->horizontalHeader()->isSectionHidden(i));
        ui->verticalLayout_2->addWidget(checkBox);
    }
}

MedicineTableSettingsForm::~MedicineTableSettingsForm() {
    delete ui;
}
void MedicineTableSettingsForm::on_buttonBox_accepted() {

    for (int i = 0; i < table_->model()->columnCount(); ++i) {
        QCheckBox* checkBox = findChild<QCheckBox*>("checkBox_" + QString::number(i));
        bool show = checkBox->isChecked();
        table_->horizontalHeader()->setSectionHidden(i, !show);
    }
    close();
}

void MedicineTableSettingsForm::on_buttonBox_rejected() {
    close();
}
