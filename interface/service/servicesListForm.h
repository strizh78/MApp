#pragma once

#include "service/service.h"
#include "interface/tableSettingsForm.h"

#include "database/databaseinterface.h"

#include <QWidget>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

#include <memory>
#include <vector>

namespace Ui {
class ServicesListForm;
}

class ServicesListForm : public QWidget {
    Q_OBJECT

public:
    explicit ServicesListForm(std::shared_ptr<DatabaseInterface> database,
                          QWidget *parent = nullptr);
    ~ServicesListForm();

private:
    void showServiceInfo(const Service& service);
    void fillServicesTable(const std::vector<Service>& servicesList);
    QList<QStandardItem*> createServiceRow(size_t row, const Service& service);

public:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void addService(const Service& service);
    void editService(const Service& oldService, const Service& editedService);

    void on_createService_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableSettings_clicked();

    void searchInTable(const QString& searchRequest);
    void on_searchLine_returnPressed();
    void on_searchLine_textChanged(const QString &arg1);

private:
    Ui::ServicesListForm *ui;
    std::shared_ptr<DatabaseInterface> database_;

    std::shared_ptr<QStandardItemModel> tableViewModel_;
};
