#pragma once

#include "service/service.h"

#include <QWidget>

#include <optional>

namespace Ui {
class ServiceEdit;
}

class ServiceEdit : public QWidget {
    Q_OBJECT

public:
    ServiceEdit(std::optional<Service> service = std::nullopt, QWidget *parent = nullptr);
    ~ServiceEdit();

private:
    void fillFormServiceInfo();

signals:
    void serviceCreateSignal(const Service& created);

private slots:
    void on_solutionBox_accepted();
    void on_solutionBox_rejected();

private:
    enum class EditType {
        CREATE,
        VIEW
    };

    Ui::ServiceEdit *ui;
    Service service_;
    EditType editType_;
};
