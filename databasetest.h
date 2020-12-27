#ifndef DATABASETEST_H
#define DATABASETEST_H

#include "databaseinterface.h"

class DatabaseTest : public DatabaseInterface
{
public:
    DatabaseTest() = default;
    std::vector<homeopathy::Drug> homeopathyDrugs() override;
    std::vector<homeopathy::Drug> availableHomeopathyDrugs() override;
    std::vector<medicine::Drug> medicineDrugs() override;
    std::vector<Service> services() override;
    std::vector<Service> notDeprecatedServices() override;
};

#endif // DATABASETEST_H
