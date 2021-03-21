#include "appointment.h"

Appointment::Appointment(const Patient& patient,
                         const Service& service,
                         const QDateTime& date)
    : patient(patient)
    , service(service)
    , date(date)
{}
