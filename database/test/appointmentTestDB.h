#pragma once

#include "itemTestInterface.h"
#include "appointment/appointment.h"

class AppointmentDBTest : public ItemDBTestInterface<Appointment> {
public:
    AppointmentDBTest(ItemDBInterface<Service>* service,
                      ItemDBInterface<Patient>* patient);
};
