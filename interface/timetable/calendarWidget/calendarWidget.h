#pragma once

#include <QDate>
#include <QWidget>

class CalendarWidget : public QWidget {
    Q_OBJECT
public:
    CalendarWidget(QWidget* parent);

    QDate selectedDate() const;
    void setSelectedDate(QDate date);

    void updateMonth();

signals:
    void dateChanged(QDate date);

public slots:
    void calendarDateClicked();

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    void setButtonStyle(QDate date, bool selected);

private:
    QDate selectedDate_;
};
