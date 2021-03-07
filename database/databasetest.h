#pragma once

#include "databaseinterface.h"

class DatabaseTest : public DatabaseInterface {
public:
    DatabaseTest();

    void homeopathyDrugs(std::vector<homeopathy::Drug>& receiver) override;
    void addHomeopathyDrug(homeopathy::Drug& drug) override;
    void editHomeopathyDrug(const homeopathy::Drug& oldDrug, const homeopathy::Drug& newDrug) override;

    void medicineDrugs(std::vector<medicine::Drug>& receiver) override;
    void addMedicineDrug(medicine::Drug& drug) override;
    void editMedicineDrug(const medicine::Drug& oldDrug, const medicine::Drug& newDrug) override;

    void services(std::vector<Service>& receiver) override;
    void addService(Service& newService) override;
    void editService(const Service& oldService, const Service& editedService) override;

    void patients(std::vector<Patient>& receiver) const override;
    void addPatient(Patient& newPatient) override;
    void editPatient(const Patient& oldPatient, const Patient& editedPatient) override;

private:
    void initMedicineDrugs();
    void initHomeopathyDrugs();
    void initServices();
    void initPatients();
    int getNextCode() override;

    static std::vector<medicine::Drug> medicinesList_;
    static std::vector<homeopathy::Drug> homeopathyList_;
    static std::vector<Service> servicesList_;
    static std::vector<Patient> patientsList_;

    static int nextCode;
};

