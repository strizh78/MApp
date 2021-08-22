#pragma once

#include "database/databaseinterface.h"

#include "interface/timetable/dailyTimetable.h"

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
    void update();

    void on_servicesList_clicked();
    void on_patientsList_clicked();
    void on_medicineList_clicked();
    void on_homeopathyList_clicked();
    void on_appointmentsList_clicked();
    void on_timetable_clicked();

private:
    Ui::MainWindow *ui;
    DailyTimetable* todayTimetable;

    std::shared_ptr<DatabaseInterface> database_;
};
