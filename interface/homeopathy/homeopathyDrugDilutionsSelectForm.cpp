#include "homeopathyDrugDilutionsSelectForm.h"
#include "ui_homeopathyDrugDilutionsSelectForm.h"
#include "drugs/homeopathy.h"

#include <QCheckBox>

HomeopathyDrugDilutionsSelectForm::HomeopathyDrugDilutionsSelectForm(
        const std::vector<QString>& selectedDilutions,
        QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::HomeopathyDrugDilutionsSelectForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Window);
    fillForm(selectedDilutions);
}

HomeopathyDrugDilutionsSelectForm::~HomeopathyDrugDilutionsSelectForm() {
    delete ui;
}

void HomeopathyDrugDilutionsSelectForm::on_buttonBox_accepted() {
    std::vector<QString> selectedDilutions;

    for (auto checkBox : findChildren<QCheckBox*>())
        if (checkBox->isChecked())
            selectedDilutions.push_back(checkBox->text());

    emit dilutionsSelectedSignal(selectedDilutions);
    close();
}

void HomeopathyDrugDilutionsSelectForm::on_buttonBox_rejected() {
    close();
}

void HomeopathyDrugDilutionsSelectForm::fillForm(const std::vector<QString>& selectedDilutions) {

    for (size_t i = 0; i < homeopathy::DILUTIONS.size(); ++i){
        auto dilution = homeopathy::DILUTIONS[i];
        auto checkBox = new QCheckBox(dilution);
        if (std::find(selectedDilutions.begin(), selectedDilutions.end(), dilution) != selectedDilutions.end())
            checkBox->setChecked(true);
        ui->gridLayout->addWidget(checkBox, i / 2, i % 2);
    }
}
