#pragma once

#include <QWidget>

namespace Ui {
class PatientInfoForm;
}

class PatientInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit PatientInfoForm(QWidget *parent = nullptr);
    ~PatientInfoForm();

signals:
    void signalCreateInfo(const QString& key, const QString& value);

private slots:
    void on_solutionBox_accepted();
    void on_solutionBox_rejected();

private:
    Ui::PatientInfoForm *ui;

    friend class PatientTests;
};
