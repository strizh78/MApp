#pragma once

#include "appointment/appointment.h"
#include "database/databaseInterface.h"

#include <QWidget>

namespace Ui {
class AppointmentMiniForm;
}

class AppointmentMiniForm : public QWidget {
    Q_OBJECT

public:
    explicit AppointmentMiniForm(const Appointment& appointment,
                                 DatabasePtr database,
                                 QWidget *parent = nullptr);
    ~AppointmentMiniForm();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::AppointmentMiniForm *ui;
    DatabasePtr database_;

    Appointment appointment_;
};
