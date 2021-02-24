#include "serviceTests.h"

#include "interface/service/serviceForm.h"
#include "ui_serviceForm.h"

#include "database/databasetest.h"

#include <algorithm>

ServiceTests::ServiceTests(std::shared_ptr<DatabaseInterface> database, QObject *parent)
    : QObject(parent)
    , database_(database)
{
}

void ServiceTests::createService() {
    Service created("Test service name", 10003.14, QTime(/*hours*/ 5, /*mins*/ 45), true);

    ServiceForm serviceEdit(database_);

    serviceEdit.ui->nameEdit->setText(created.name());
    serviceEdit.ui->priceEdit->setText(QString::number(created.price()));
    serviceEdit.ui->durationEdit->setTime(created.duration());
    serviceEdit.ui->switchActive->setChecked(!created.isDeprecated());

    serviceEdit.on_solutionBox_accepted();

    std::vector<Service> currentServices;
    database_->services(currentServices);
    Q_ASSERT(std::find(currentServices.begin(), currentServices.end(), created) != currentServices.end());
}

void ServiceTests::editService() {
    Service created("Test service name 2", 0.12, QTime(/*hours*/ 1, /*mins*/ 0), false);
    Service edited("Test service name edited", 100, QTime(/*hours*/ 0, /*mins*/ 55), true);
    database_->addService(created);

    ServiceForm serviceEdit(database_, created);

    serviceEdit.ui->nameEdit->setText(edited.name());
    serviceEdit.ui->priceEdit->setText(QString::number(edited.price()));
    serviceEdit.ui->durationEdit->setTime(edited.duration());
    serviceEdit.ui->switchActive->setChecked(!edited.isDeprecated());

    serviceEdit.on_solutionBox_accepted();

    std::vector<Service> currentServices;
    database_->services(currentServices);
    Q_ASSERT(std::find(currentServices.begin(), currentServices.end(), created) == currentServices.end());
    Q_ASSERT(std::find(currentServices.begin(), currentServices.end(), edited) != currentServices.end());
}
