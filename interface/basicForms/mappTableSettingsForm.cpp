#include "mappTableSettingsForm.h"
#include "ui_mappTableSettingsForm.h"

#include "interface/basicForms/tableSettingsForm.h"

MAppTableSettingsForm::MAppTableSettingsForm(QTabWidget* tabs, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MAppTableSettingsForm)
    , tabs_(tabs)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Window);

    ui->useBinSwitch->setChecked(tabs_->tabBar()->isVisible());

    if (tabs_->currentIndex() == 0) {
         ui->columnSettings->setHeaders(tabs_->findChild<QTableView*>("mainTable")->horizontalHeader());
    }
    else {
         ui->columnSettings->setHeaders(tabs_->findChild<QTableView*>("binTable")->horizontalHeader());
    }
}

MAppTableSettingsForm::~MAppTableSettingsForm() {
    delete ui;
}

void MAppTableSettingsForm::on_solutionBox_accepted() {
    bool useBin = ui->useBinSwitch->isChecked();
    tabs_->tabBar()->setVisible(useBin);

    if (!useBin) {
        tabs_->setCurrentIndex(0);
    }
    ui->columnSettings->accept();
    close();
}

void MAppTableSettingsForm::on_solutionBox_rejected() {
    close();
}

