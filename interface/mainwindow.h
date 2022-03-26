#pragma once

#include "database/databaseInterface.h"

#include "interface/timetable/dailyTimetable.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(DatabasePtr database,
               QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_servicesList_clicked();
    void on_patientsList_clicked();
    void on_medicineList_clicked();
    void on_homeopathyList_clicked();
    void on_appointmentsList_clicked();
    void on_timetable_clicked();

private:
    template <class T>
    void openWidget();

    template <class F>
    QAction* addActionToMenu(const QIcon& icon, const QString& text,
                             F slotName);

private:
    Ui::MainWindow *ui;

    DatabasePtr database_;
    DailyTimetable* todayTimetable;
};
