#pragma once

#include "drugs/dosage.h"

#include <QWidget>
#include <QComboBox>
#include <QStandardItemModel>

namespace Ui {
class DosageForm;
}

class DosageForm : public QWidget {
    Q_OBJECT

public:
    DosageForm(const Dosage& dosage, QWidget *parent = nullptr);
    ~DosageForm();

signals:
    void dosageEditSignal(const Dosage& dosage);
private slots:
    void on_ageFromSpinBox_valueChanged(int value);
    void on_ageToSpinBox_valueChanged(int value);
    void on_ageFromCheckBox_stateChanged(int state);
    void on_ageToCheckBox_stateChanged(int state);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    void initModels();
    void initModel(int idx,
                   const QString& monthStr,
                   const QString& yearStr);
    void spinBoxValueChanged(int value, QComboBox* comboBox);
    void setComboModel(int value, QComboBox* comboBox);
    int getAge(const QString& end);
    void setAge(int ageInMonths, const QString& end);
    std::pair<int, int> parseAge(int ageInMonths);
private:
    Ui::DosageForm *ui;
    Dosage dosage_;
    bool isModified_;
    QStandardItemModel* model_[2];
};
