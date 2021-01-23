#pragma once

#include "databaseinterface.h"

class DatabaseTest : public DatabaseInterface {
public:
    DatabaseTest() = default;

    void homeopathyDrugs(std::vector<homeopathy::Drug>& receiver) override;
    void availableHomeopathyDrugs(std::vector<homeopathy::Drug>& receiver) override;
    void medicineDrugs(std::vector<medicine::Drug>& receiver) override;

    void services(std::vector<Service>& receiver) override;
    void notDeprecatedServices(std::vector<Service>& receiver) override;
    void addService(const Service& newService) override;
    void editService(const Service& oldService, const Service& editedService) override;

    virtual void patients(std::vector<Patient>& receiver) const override;
    virtual void addPatient(const Patient& newPatient) override;
    virtual void editPatient(const Patient& oldPatient, const Patient& editedPatient) override;

private:
    static const std::vector<Service> initServices();
    static const std::vector<Patient> initPatients();

    static std::vector<Service> servicesList_;
    static std::vector<Patient> patientsList_;
};

