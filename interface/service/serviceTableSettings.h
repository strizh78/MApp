#pragma once

#include <QWidget>

#include <vector>

namespace Ui {
class ServiceTableSettings;
}

class ServiceTableSettings : public QWidget
{
    Q_OBJECT

public:
    explicit ServiceTableSettings(QWidget *parent = nullptr);
    ~ServiceTableSettings();

signals:
    void signalChangeColumnsDisplay(std::vector<bool> columns);

private slots:
    void on_tableSettingsSolutionBox_accepted();
    void on_tableSettingsSolutionBox_rejected();

private:
    Ui::ServiceTableSettings *ui;
};
