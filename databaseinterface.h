#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include "homeopathy.h"
#include "medicines.h"
#include "service.h"

#include <vector>

class DatabaseInterface
{
public:
    DatabaseInterface() = default;

    virtual std::vector<homeopathy::Drug> homeopathyDrugs() = 0;
    virtual std::vector<homeopathy::Drug> availableHomeopathyDrugs() = 0;
    virtual std::vector<medicine::Drug()> medicineDrugs() = 0;
    virtual std::vector<Service> services() = 0;
    virtual std::vector<Service> notDeprecatedServices() = 0;
};

#endif // DATABASEINTERFACE_H
