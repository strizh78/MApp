#include "appointmentEntry.h"

#include "interface/appointment/appointmentForm.h"

#include "interface/utils.h"
#include "timetable/timetableUtils.h"

std::shared_ptr<TimetableEntry> getEntry(const Appointment& x, const TimetableDrawSettings& settings) {
    return std::make_shared<TimetableAppointment>(x, settings);
}

TimetableAppointment::TimetableAppointment(const Appointment &appointment, const TimetableDrawSettings &settings)
    : TimetableEntry(appointment, settings)
    , appointment(appointment)
{
}

void TimetableAppointment::openForm(std::shared_ptr<DatabaseInterface> database, QWidget *parent, bool show) const {
    auto * appointmentViewForm = new AppointmentForm(database, appointment, parent);
    parent->connect(appointmentViewForm, SIGNAL(appointmentEditSignal(Appointment)),
                    parent, SLOT(update()));
    if (show)
        showAsWindowModal(appointmentViewForm);
    return;
}

bool TimetableAppointment::isDateEquals(const QDate &timetableDate) const {
    return timetableDate == appointment.date.date();
}

bool TimetableAppointment::tryMoveEntry(const QTime &diff, std::shared_ptr<DatabaseInterface> database,
                                        int minHour, int maxHour)
{
    if (appointment.isConducted) {
        return false;
    }

    Appointment appointmentNew = appointment;
    appointmentNew.date.setTime(appointmentNew.date.time().addSecs(toSeconds(diff)));

    if (appointmentNew.date.time().hour() < minHour ||
        appointmentNew.date.time().hour() >= maxHour - 1)
    {
        return false;
    }

    if (isTimeSlotAvailable(database.get(), appointmentNew, appointmentNew.date, appointmentNew.service.duration)) {
        database->editAppointment(appointmentNew);
        return true;
    }

    return false;
}
