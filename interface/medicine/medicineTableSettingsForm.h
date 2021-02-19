#pragma once

#include <QDialog>
#include <QHeaderView>

namespace Ui {
class MedicineTableSettingsForm;
}

class MedicineTableSettingsForm : public QDialog {
    Q_OBJECT

public:
    MedicineTableSettingsForm(QHeaderView* headers,
                              QWidget* parent = nullptr);
    ~MedicineTableSettingsForm();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    void setCheckBox(QString text, int num);

private:
    Ui::MedicineTableSettingsForm *ui;
    QHeaderView* headerView_;
};

