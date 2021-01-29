#pragma once

#include <QWidget>
#include <QCheckBox>

#include <vector>

namespace Ui {
class TableSettingsForm;
}

class TableSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit TableSettingsForm(const QStringList& columnNames, QWidget *parent = nullptr);
    ~TableSettingsForm();

signals:
    void signalChangeColumnsDisplay(std::vector<bool> columns);

private slots:
    void on_tableSettingsSolutionBox_accepted();
    void on_tableSettingsSolutionBox_rejected();

private:
    Ui::TableSettingsForm *ui;
    std::vector<QCheckBox> columnCheckBoxes;
};
