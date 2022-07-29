#include "appointmentTestDB.h"

template <>
std::vector<Appointment> ItemDBTestInterface<Appointment>::list_ = {};
template <>
int ItemDBTestInterface<Appointment>::code_ = 0;

AppointmentDBTest::AppointmentDBTest(ItemDBInterface<Service>* service,
                                     ItemDBInterface<Patient>* patient)
{
    QDate today = QDate::currentDate();
    QDate yesterday = QDate::currentDate().addDays(-1);
    QDate tomorrow = QDate::currentDate().addDays(1);

    std::vector<Service> services;
    service->list(services);

    std::vector<Patient> patients;
    patient->list(patients);
    std::vector<Appointment> appointmentsList = {
        Appointment(patients[0], services[0], QDateTime(today, {8, 10})),
        Appointment(patients[4], services[1], QDateTime(today, {8, 30})),
        Appointment(patients[6], services[2], QDateTime(today, {9, 00})),
        Appointment(patients[1], services[1], QDateTime(today, {11, 00})),
        Appointment(patients[1], services[1], QDateTime(today, {11, 30})),

        Appointment(patients[5], services[6], QDateTime(today, {12, 00})),
        Appointment(patients[2], services[8], QDateTime(today, {13, 00})),

        Appointment(patients[3], services[5], QDateTime(today, {14, 10})),

        Appointment(patients[1], services[0], QDateTime(today, {15, 00})),
        Appointment(patients[2], services[1], QDateTime(today, {15, 20})),
        Appointment(patients[3], services[0], QDateTime(today, {15, 50})),
        Appointment(patients[4], services[0], QDateTime(today, {16, 10})),
        Appointment(patients[5], services[1], QDateTime(today, {17, 00})),
        Appointment(patients[5], services[0], QDateTime(today, {17, 30})),
        Appointment(patients[5], services[1], QDateTime(today, {17, 50})),

        Appointment(patients[4], services[2], QDateTime(today, {19, 00})),
        Appointment(patients[5], services[3], QDateTime(today, {20, 30})),

        Appointment(patients[1], services[8], QDateTime(yesterday, {8, 10})),
        Appointment(patients[3], services[8], QDateTime(yesterday, {9, 45})),
        Appointment(patients[0], services[1], QDateTime(yesterday, {14, 10})),
        Appointment(patients[5], services[2], QDateTime(yesterday, {16, 00})),
        Appointment(patients[2], services[8], QDateTime(yesterday, {20, 00})),
        Appointment(patients[1], services[7], QDateTime(yesterday, {21, 35})),

        Appointment(patients[2], services[0], QDateTime(tomorrow, {8, 10})),
        Appointment(patients[4], services[1], QDateTime(tomorrow, {12, 45})),
        Appointment(patients[3], services[3], QDateTime(tomorrow, {14, 10}))
    };

    for (auto& appointment : appointmentsList) {
        if (appointment.date.date() == yesterday) {
            appointment.isConducted = true;
        }
    }
    appointmentsList[1].isConducted = true;
    appointmentsList[7].isConducted = false;


    for (auto appointment : appointmentsList)
        add(appointment);
}
