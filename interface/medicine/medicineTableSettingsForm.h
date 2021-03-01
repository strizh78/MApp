#pragma once

#include <QHeaderView>
#include <QWidget>

namespace Ui {
class MedicineTableSettingsForm;
}

class MedicineTableSettingsForm : public QWidget {
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

