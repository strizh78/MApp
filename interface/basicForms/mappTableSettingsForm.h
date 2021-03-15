#pragma once

#include <QTabWidget>
#include <QWidget>

namespace Ui {
class MAppTableSettingsForm;
}

class MAppTableSettingsForm : public QWidget {
    Q_OBJECT

public:
     MAppTableSettingsForm(QTabWidget* tabs, QWidget *parent = nullptr);
    ~MAppTableSettingsForm();

private slots:
     void on_solutionBox_accepted();
     void on_solutionBox_rejected();

private:
    Ui::MAppTableSettingsForm *ui;
    QTabWidget* tabs_;
};
