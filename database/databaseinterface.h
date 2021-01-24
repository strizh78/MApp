#pragma once

#include "drugs/homeopathy.h"
#include "drugs/medicines.h"

#include "service/service.h"

#include <vector>

class DatabaseInterface
{
public:
    DatabaseInterface() = default;
    virtual ~DatabaseInterface() = default;

    virtual void homeopathyDrugs(std::vector<homeopathy::Drug>& ) = 0;
    virtual void availableHomeopathyDrugs(std::vector<homeopathy::Drug>& ) = 0;

    virtual void medicineDrugs(std::vector<medicine::Drug>&) = 0;
    virtual void addMedicineDrug(const medicine::Drug& drug) = 0;
    virtual void editMedicineDrug(const medicine::Drug& oldDrug, const medicine::Drug& newDrug) = 0;

    virtual void services(std::vector<Service>& ) = 0;
    virtual void notDeprecatedServices(std::vector<Service>& ) = 0;
    virtual void addService(const Service& newService) = 0;
    virtual void editService(const Service& oldService, const Service& editedService) = 0;

};
