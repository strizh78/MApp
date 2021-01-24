#pragma once

#include "databaseinterface.h"

class DatabaseTest : public DatabaseInterface {
public:
    DatabaseTest() = default;

    void homeopathyDrugs(std::vector<homeopathy::Drug>& receiver) override;
    void availableHomeopathyDrugs(std::vector<homeopathy::Drug>& receiver) override;

    void medicineDrugs(std::vector<medicine::Drug>& receiver) override;
    void addMedicineDrug(const medicine::Drug& drug) override;
    void editMedicineDrug(const medicine::Drug& oldDrug, const medicine::Drug& newDrug) override;

    void services(std::vector<Service>& receiver) override;
    void notDeprecatedServices(std::vector<Service>& receiver) override;
    void addService(const Service& newService) override;
    void editService(const Service& oldService, const Service& editedService) override;

private:
    static const std::vector<medicine::Drug> initMedicineDrugs();
    static const std::vector<Service> initServices();

    static std::vector<medicine::Drug> medicinesList_;
    static std::vector<Service> servicesList_;
};

