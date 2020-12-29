#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "interface/service/servicesList.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_servicesList_clicked() {
    auto* servicesList = new ServicesList;
    servicesList->setAttribute(Qt::WA_DeleteOnClose, true);
    servicesList->show();
}
