#pragma once

#include "MAppBaseObj/mappBaseObj.h"

#include "patient/patient.h"
#include "service/service.h"

#include "drugs/medicines.h"
#include "drugs/homeopathy.h"

#include <QDateTime>

#include <vector>

class Appointment : public MAppBaseObj {
public:
    Appointment() = default;
    Appointment(const Patient& patient,
                const Service& service,
                const QDateTime& date);

public:
    Patient patient;
    Service service;
    homeopathy::Drug homeopathy;
    std::vector<medicine::Drug> medicines;

    QDateTime date;

    QString record;
};
