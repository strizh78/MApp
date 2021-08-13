#pragma once

#include <QWidget>
#include <QHeaderView>

#include <optional>
#include <vector>

namespace Ui {
class TableSettingsForm;
}

class TableSettingsForm : public QWidget {
    Q_OBJECT

public:
    TableSettingsForm(QHeaderView* headerView,
                      QWidget *parent = nullptr);
    TableSettingsForm(QWidget* parent = nullptr);
    ~TableSettingsForm();

    void setHeaders(QHeaderView* headerView);
    void accept();
    void reject();

signals:
    void signalChangeColumnsDisplay(std::vector<bool> columns);

private:
    void addCheckBox(const QString& text, int num);
    void hideSections();

private:
    Ui::TableSettingsForm *ui;
    QHeaderView* headerView_;
};
