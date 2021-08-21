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
    enum AppointmentTimeType {
        PAST,
        PRESENT,
        FUTURE
    };

    AppointmentTimeType getTimeType() const {
        const int secondsIn15Mins = 15 * 60;
        QDateTime begin = date;
        QDateTime end = date.addSecs(service.duration.hour() * 60 * 60 + service.duration.minute() * 60);

        QDateTime pastTime = QDateTime::currentDateTime().addSecs(-secondsIn15Mins);
        QDateTime futureTime = QDateTime::currentDateTime().addSecs(secondsIn15Mins);

        if (end < pastTime) {
            return PAST;
        } else if (begin > futureTime) {
            return FUTURE;
        } else {
            return PRESENT;
        }
    }

public:
    bool isConducted = false;

    Patient patient;
    Service service;
    homeopathy::Drug homeopathy;
    std::vector<medicine::Drug> medicines;

    QDateTime date;

    QString record;
};
