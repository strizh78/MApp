#pragma once

#include "service/service.h"
#include "interface/basicForms/mappTable.h"

#include "database/databaseinterface.h"

#include <QStandardItem>
#include <QStyledItemDelegate>
#include <QWidget>

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

private slots:
    void onAddButtonClicked();
    void onEditButtonClicked(const QVariant &data);
    void onDeleteButtonClicked(const QVariant &data);
    void addService(const Service& service);
    void editService(const Service& editedService);

private:
    void setupTableSettings();
    void fillServicesTable(const std::vector<Service>& servicesList);
    QList<QStandardItem*> createServiceRow(const Service& service);

private:
    Ui::ServicesListForm *ui;
    std::shared_ptr<DatabaseInterface> database_;
};
