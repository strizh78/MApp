#pragma once

#include "databaseinterface.h"

class DatabaseTest : public DatabaseInterface {
public:
    DatabaseTest();

    void homeopathyDrugs(std::vector<homeopathy::Drug>& receiver) override;
    void addHomeopathyDrug(homeopathy::Drug& drug) override;
    void editHomeopathyDrug(const homeopathy::Drug& oldDrug, homeopathy::Drug& newDrug) override;

    void medicineDrugs(std::vector<medicine::Drug>& receiver) override;
    void addMedicineDrug(medicine::Drug& drug) override;
    void editMedicineDrug(const medicine::Drug& oldDrug, medicine::Drug& newDrug) override;

    void services(std::vector<Service>& receiver) override;
    void addService(Service& newService) override;
    void editService(const Service& oldService, Service& editedService) override;

    void patients(std::vector<Patient>& receiver) const override;
    void addPatient(Patient& patient) override;
    void editPatient(const Patient& oldPatient, Patient& editedPatient) override;

    void appointments(std::vector<Appointment>& receiver) const override;
    void addAppointment(Appointment& appointment) override;
    void editAppointment(const Appointment& appointment) override;

    void events(std::vector<Event>&) const override;
    void addEvent(Event&) override;
    void editEvent(const Event&) override;

private:
    void initEvents();
    void initAppointments();
    void initMedicineDrugs();
    void initHomeopathyDrugs();
    void initServices();
    void initPatients();
    int getNextCode() override;

    static std::vector<medicine::Drug> medicinesList_;
    static std::vector<homeopathy::Drug> homeopathyList_;
    static std::vector<Service> servicesList_;
    static std::vector<Patient> patientsList_;
    static std::vector<Appointment> appointmentsList_;
    static std::vector<Event> eventsList_;

    static int nextCode;
};

