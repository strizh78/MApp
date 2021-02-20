#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "interface/medicine/medicineDrugListForm.h"
#include "interface/service/servicesList.h"
#include "interface/patient/patientsListForm.h"

MainWindow::MainWindow(std::shared_ptr<DatabaseInterface> database,
                       QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , database_(database)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_servicesList_clicked() {
    auto* servicesList = new ServicesList(database_);
    servicesList->setAttribute(Qt::WA_DeleteOnClose, true);
    servicesList->show();
}

void MainWindow::on_medicineList_clicked() {
    auto* medicinesList = new MedicineDrugListForm(database_);
    medicinesList->setAttribute(Qt::WA_DeleteOnClose, true);
    medicinesList->show();
}

void MainWindow::on_patientsList_clicked() {
    auto* patientsList = new PatientsListForm(database_);
    patientsList->setAttribute(Qt::WA_DeleteOnClose, true);
    patientsList->show();
}