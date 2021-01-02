#pragma once

#include "databaseinterface.h"

class DatabaseTest : public DatabaseInterface {
public:
    DatabaseTest();

    void homeopathyDrugs(std::vector<homeopathy::Drug>& receiver) override;
    void availableHomeopathyDrugs(std::vector<homeopathy::Drug>& receiver) override;
    void medicineDrugs(std::vector<medicine::Drug>& receiver) override;

    void services(std::vector<Service>& receiver) override;
    void notDeprecatedServices(std::vector<Service>& receiver) override;
    void addService(const Service& newService) override;

private:
    void initServices();

    static std::vector<Service> servicesList_;
};

