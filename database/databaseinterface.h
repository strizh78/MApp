#pragma once

#include "drugs/homeopathy.h"
#include "drugs/medicines.h"

#include "service/service.h"

#include "patient/patient.h"

#include <vector>

class DatabaseInterface
{
public:
    DatabaseInterface() = default;
    virtual ~DatabaseInterface() = default;

    virtual void homeopathyDrugs(std::vector<homeopathy::Drug>& ) = 0;
    virtual void availableHomeopathyDrugs(std::vector<homeopathy::Drug>& ) = 0;
    virtual void medicineDrugs(std::vector<medicine::Drug>&) = 0;

    virtual void services(std::vector<Service>& ) = 0;
    virtual void notDeprecatedServices(std::vector<Service>& ) = 0;
    virtual void addService(const Service& ) = 0;
    virtual void editService(const Service& , const Service& ) = 0;

    virtual void patients(std::vector<Patient>&) const = 0;
    virtual void addPatient(const Patient&) = 0;
    virtual void editPatient(const Patient& , const Patient&) = 0;
};
