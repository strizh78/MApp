#include "servicetests.h"

#include "interface/service/serviceEdit.h"
#include "ui_serviceEdit.h"

#include "database/databasetest.h"

#include <algorithm>

ServiceTests::ServiceTests(QObject *parent)
    : QObject(parent)
    , database_(std::make_shared<DatabaseTest>())
{
}

void ServiceTests::CreateService() {
    Service created("Test service name", 10003.14, QTime(/*hours*/ 5, /*mins*/ 45), true);

    ServiceEdit serviceEdit(database_);

    serviceEdit.ui->nameEdit->setText(created.name());
    serviceEdit.ui->priceEdit->setText(QString::number(created.price()));
    serviceEdit.ui->durationEdit->setTime(created.duration());
    serviceEdit.ui->switchActive->setChecked(!created.isDeprecated());

    serviceEdit.on_solutionBox_accepted();

    std::vector<Service> currentServices;
    database_->services(currentServices);
    Q_ASSERT(std::find(currentServices.begin(), currentServices.end(), created) != currentServices.end());
}
