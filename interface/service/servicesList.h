#pragma once

#include "service/service.h"
#include "serviceTableSettings.h"

#include "database/databaseinterface.h"

#include <QWidget>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

#include <vector>

namespace Ui {
class ServicesList;
}

class ServicesList : public QWidget {
    Q_OBJECT

public:
    explicit ServicesList(QWidget *parent = nullptr);
    ~ServicesList();

private:
    void showServiceInfo(const Service& service);
    void fillServicesTable(const std::vector<Service>& servicesList);
    QList<QStandardItem*> createServiceRow(size_t row, const Service& service);

public:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void addService(const Service& service);

    void on_createService_clicked();

    void on_selectService_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);

    void changeColumnsDisplayOption(std::vector<bool> columns);
    void on_tableSettings_clicked();

    void searchInTable(const QString& searchRequest);
    void on_searchLine_returnPressed();
    void on_searchLine_textChanged(const QString &arg1);

private:
    DatabaseInterface* databaseInterface_;

    Ui::ServicesList *ui;
    QStandardItemModel* tableViewModel_;
    ServiceTableSettings* tableSettingsForm_ = nullptr;
};
