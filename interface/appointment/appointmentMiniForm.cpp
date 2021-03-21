#include "appointmentMiniForm.h"
#include "ui_AppointmentMiniForm.h"

#include "appointmentForm.h"

AppointmentMiniForm::AppointmentMiniForm(const Appointment& appointment,
                                         std::shared_ptr<DatabaseInterface> database,
                                         QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppointmentMiniForm)
    , database_(database)
    , appointment_(appointment)
{
    ui->setupUi(this);

    ui->dateTime->setText(appointment_.date.toString("d.MM.yy h:mm"));
    ui->service->setText(appointment_.service.name());
}

AppointmentMiniForm::~AppointmentMiniForm() {
    delete ui;
}

void AppointmentMiniForm::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    auto* appointmentViewForm = new AppointmentForm(database_, AppointmentForm::EDIT, appointment_);

    appointmentViewForm->setAttribute(Qt::WA_DeleteOnClose, true);
    appointmentViewForm->show();
}
