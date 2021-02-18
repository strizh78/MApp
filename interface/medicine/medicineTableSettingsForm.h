#pragma once

#include <QDialog>
#include <QTableView>

namespace Ui {
class MedicineTableSettingsForm;
}

class MedicineTableSettingsForm : public QDialog
{
    Q_OBJECT

public:

    MedicineTableSettingsForm(QTableView* table,
                              QWidget* parent = nullptr);
    ~MedicineTableSettingsForm();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::MedicineTableSettingsForm *ui;
    QTableView* table_;

};

