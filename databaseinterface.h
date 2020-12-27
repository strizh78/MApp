#pragma once

#include "homeopathy.h"
#include "medicines.h"
#include "service.h"

#include <vector>

class DatabaseInterface
{
public:
    DatabaseInterface() = default;

    virtual void homeopathyDrugs(std::vector<homeopathy::Drug>& ) = 0;
    virtual void availableHomeopathyDrugs(std::vector<homeopathy::Drug>& ) = 0;
    virtual void medicineDrugs(std::vector<medicine::Drug>&) = 0;
    virtual void services(std::vector<Service>& ) = 0;
    virtual void notDeprecatedServices(std::vector<Service>& ) = 0;
};
