#pragma once

#include "service/service.h"
#include "database/databaseinterface.h"

#include <QWidget>

#include <optional>

namespace Ui {
class ServiceForm;
}

class ServiceForm : public QWidget {
    Q_OBJECT

public:
    ServiceForm(std::shared_ptr<DatabaseInterface> database,
                std::optional<Service> service = std::nullopt,
                QWidget *parent = nullptr);
    ~ServiceForm();

private:
    void fillFormServiceInfo();

signals:
    void serviceCreateSignal(const Service& created);
    void serviceEditSignal(const Service& editedService);

private slots:
    void on_solutionBox_accepted();
    void on_solutionBox_rejected();

private:
    void setEditEnabled(bool enabled);

    Ui::ServiceForm *ui;
    std::shared_ptr<DatabaseInterface> database_;

    Service service_;

    friend class ServiceTests;
};
