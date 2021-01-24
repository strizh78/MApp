#pragma once

#include "database/databaseinterface.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<DatabaseInterface> database,
               QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_servicesList_clicked();

    void on_medicineList_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<DatabaseInterface> database_;
};
