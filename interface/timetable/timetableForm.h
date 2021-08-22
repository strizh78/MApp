#pragma once

#include "database/databaseinterface.h"

#include <QWidget>

namespace Ui {
class TimetableForm;
}

class TimetableForm : public QWidget {
    Q_OBJECT

public:
    explicit TimetableForm(std::shared_ptr<DatabaseInterface> database,
                           QWidget *parent = nullptr);
    ~TimetableForm();

private slots:
    void on_addEventBtn_clicked();

    void on_leftDateBtn_clicked();
    void on_rightDateBtn_clicked();
    void on_todayDateBtn_clicked();

    void on_calendarWidget_clicked(const QDate &date);
    void on_calendarWidget_activated(const QDate &date);

private:
    void setDate(const QDate& date);

private:
    Ui::TimetableForm *ui;
    std::shared_ptr<DatabaseInterface> database_;
};
