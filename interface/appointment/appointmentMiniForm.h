#pragma once

#include "appointment/appointment.h"
#include "database/databaseinterface.h"

#include <QWidget>

namespace Ui {
class AppointmentMiniForm;
}

class AppointmentMiniForm : public QWidget {
    Q_OBJECT

public:
    explicit AppointmentMiniForm(const Appointment& appointment,
                                 std::shared_ptr<DatabaseInterface> database,
                                 QWidget *parent = nullptr);
    ~AppointmentMiniForm();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::AppointmentMiniForm *ui;
    std::shared_ptr<DatabaseInterface> database_;

    Appointment appointment_;
};
