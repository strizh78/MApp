#include "medicineTableSettingsForm.h"
#include "ui_medicineTableSettingsForm.h"

#include <QCheckBox>

MedicineTableSettingsForm::MedicineTableSettingsForm(QHeaderView* headers,
                                                     QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MedicineTableSettingsForm)
    , headerView_(headers)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Window);
    ui->verticalLayout_2->setAlignment(Qt::AlignTop);
    auto* model = headerView_->model();

    for (int i = 0; i < model->columnCount(); ++i)
        setCheckBox(model->headerData(i, Qt::Horizontal).toString(), i);
}

MedicineTableSettingsForm::~MedicineTableSettingsForm() {
    delete ui;
}

void MedicineTableSettingsForm::on_buttonBox_accepted() {
    for (int i = 0; i < headerView_->model()->columnCount(); ++i) {
        QCheckBox* checkBox = findChild<QCheckBox*>("checkBox_" + QString::number(i));
        bool show = checkBox->isChecked();
        headerView_->setSectionHidden(i, !show);
    }
    close();
}

void MedicineTableSettingsForm::on_buttonBox_rejected() {
    close();
}

void MedicineTableSettingsForm::setCheckBox(QString text, int num) {
    auto checkBox = new QCheckBox(text);
    checkBox->setObjectName("checkBox_" + QString::number(num));
    checkBox->setChecked(!headerView_->isSectionHidden(num));
    ui->verticalLayout_2->addWidget(checkBox);
}
