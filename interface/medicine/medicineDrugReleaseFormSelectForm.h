#pragma once

#include "drugs/medicines.h"

#include <QLabel>
#include <QWidget>

namespace Ui {
class MedicineDrugReleaseFormSelectForm;
}

class MedicineDrugReleaseFormSelectForm : public QWidget {
    Q_OBJECT

public:
     MedicineDrugReleaseFormSelectForm(const std::vector<ReleaseForm>& selectedReleaseForms,
                                       QLabel* label,
                                       QWidget *parent = nullptr);
    ~MedicineDrugReleaseFormSelectForm();

signals:
     void releaseFormsSelectedSignal(QLabel* label, const std::vector<QString>& data);

private slots:
     void on_buttonBox_accepted();
     void on_buttonBox_rejected();

private:
    void fillForm(const std::vector<ReleaseForm>& selectedReleaseForms);

private:
    Ui::MedicineDrugReleaseFormSelectForm *ui;
    QLabel* label_;
};

