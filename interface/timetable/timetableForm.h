#pragma once

#include "database/databaseInterface.h"
#include "interface/interfaceUtils.h"

#include <QWidget>

class TimetableEvent;

namespace Ui {
class TimetableForm;
}

class TimetableForm : public QWidget {
    Q_OBJECT

public:
    explicit TimetableForm(DatabasePtr database,
                           QWidget *parent = nullptr);
    ~TimetableForm();

private slots:
    void updateData();

    void on_addEventBtn_clicked();

    void on_leftDateBtn_clicked();
    void on_rightDateBtn_clicked();
    void on_todayDateBtn_clicked();

    void calendarDateChanged(QDate date);

    void on_monthComboBox_currentIndexChanged(int index);
    void on_yearComboBox_currentTextChanged(const QString &arg1);

private:
    void setDate(const QDate& date);
    void timerEvent(QTimerEvent *event) override;

private:
    Ui::TimetableForm *ui;

    QDate date_;
    DatabasePtr database_;
};
