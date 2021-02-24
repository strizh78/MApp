#include "medicineDrugReleaseFormSelectForm.h"
#include "ui_medicineDrugReleaseFormSelectForm.h"

#include <QCheckBox>

#include <algorithm>

MedicineDrugReleaseFormSelectForm::MedicineDrugReleaseFormSelectForm(const std::vector<ReleaseForm>& selectedReleaseForms,
                                                                     QLabel* label,
                                                                     QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MedicineDrugReleaseFormSelectForm)
    , label_(label)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Window);
    setWindowTitle("Формы выпуска");
    fillForm(selectedReleaseForms);
}

MedicineDrugReleaseFormSelectForm::~MedicineDrugReleaseFormSelectForm() {
    delete ui;
}

void MedicineDrugReleaseFormSelectForm::on_buttonBox_accepted() {
    std::vector<QString> selectedReleaseForms;

    for (auto checkBox : findChildren<QCheckBox*>()) {
        if (checkBox->isChecked())
            selectedReleaseForms.push_back(checkBox->text());
    }

    emit releaseFormsSelectedSignal(label_, selectedReleaseForms);
    close();
}

void MedicineDrugReleaseFormSelectForm::on_buttonBox_rejected() {
    close();
}

void MedicineDrugReleaseFormSelectForm::fillForm(const std::vector<ReleaseForm>& selectedForms) {
    for(auto releaseForm : medicine::RELEASE_FORMS) {
        auto checkBox = new QCheckBox(releaseForm);
        if (std::find(selectedForms.begin(), selectedForms.end(), releaseForm) != selectedForms.end())
            checkBox->setChecked(true);
        ui->verticalLayout_2->addWidget(checkBox);
    }
}
