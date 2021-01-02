#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "interface/service/servicesList.h"

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
