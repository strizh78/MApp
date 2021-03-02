#pragma once

#include <QLabel>
#include <QString>
#include <QWidget>

namespace Ui {
class HomeopathyDrugDilutionsSelectForm;
}

class HomeopathyDrugDilutionsSelectForm : public QWidget
{
    Q_OBJECT

public:
    explicit HomeopathyDrugDilutionsSelectForm(const std::vector<QString>& selectedDilutions,
                                               QWidget *parent = nullptr);
    ~HomeopathyDrugDilutionsSelectForm();

signals:
     void dilutionsSelectedSignal(const std::vector<QString>& data);

private slots:
     void on_buttonBox_accepted();
     void on_buttonBox_rejected();

private:
    void fillForm(const std::vector<QString>& selectedDilutions);

private:
    Ui::HomeopathyDrugDilutionsSelectForm *ui;
};
