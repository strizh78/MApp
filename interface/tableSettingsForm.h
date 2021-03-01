#pragma once

#include <QWidget>
#include <QHeaderView>

#include <vector>

namespace Ui {
class TableSettingsForm;
}

class TableSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit TableSettingsForm(QHeaderView* headerView,
                               QWidget *parent = nullptr);
    ~TableSettingsForm();

signals:
    void signalChangeColumnsDisplay(std::vector<bool> columns);

private slots:
    void on_tableSettingsSolutionBox_accepted();
    void on_tableSettingsSolutionBox_rejected();

private:
    void addCheckBox(const QString& text, int num);

private:
    Ui::TableSettingsForm *ui;
    QHeaderView* headerView_;
};
