#pragma once

#include "service/service.h"
#include "database/databaseinterface.h"

#include <QWidget>

#include <optional>

namespace Ui {
class ServiceEdit;
}

class ServiceEdit : public QWidget {
    Q_OBJECT

public:
    ServiceEdit(std::shared_ptr<DatabaseInterface> database,
                std::optional<Service> service = std::nullopt, QWidget *parent = nullptr);
    ~ServiceEdit();

private:
    void fillFormServiceInfo();

signals:
    void serviceCreateSignal(const Service& created);
    void serviceEditSignal(const Service& oldService, const Service& editedService);

private slots:
    void on_solutionBox_accepted();
    void on_solutionBox_rejected();

private:
    enum class EditType {
        CREATE,
        EDIT
    };

    Ui::ServiceEdit *ui;
    std::shared_ptr<DatabaseInterface> database_;

    Service service_;
    EditType editType_;

    friend class ServiceTests;
};
