#pragma once

#include <QWidget>

namespace Ui {
class AppointmentRecordForm;
}

class AppointmentRecordForm : public QWidget {
    Q_OBJECT

public:
    explicit AppointmentRecordForm(QWidget *parent = nullptr);
    ~AppointmentRecordForm();

    void setEditEnabled(bool enabled);

    void setHtml(const QString& text);
    QString getHtml();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_newTabBtn_clicked();
    void on_returnInWindow_clicked();

    void on_solutionBox_accepted();

private:
    void changeButtonsVisibility(bool isWidget);

private:
    Ui::AppointmentRecordForm *ui;
};
