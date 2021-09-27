#include "servicesListForm.h"
#include "ui_servicesListForm.h"
#include "serviceForm.h"

#include "interface/utils.h"

ServicesListForm::ServicesListForm(DatabasePtr database,
                           QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServicesListForm)
    , database_(database)
{
    ui->setupUi(this);

    std::vector<Service> servicesList;
    database_->service->list(servicesList);
    setupTableSettings();
    fillServicesTable(servicesList);
}

ServicesListForm::~ServicesListForm() {
    delete ui;
}

void ServicesListForm::onAddButtonClicked() {
    auto* serviceCreateForm = new ServiceForm(database_);
    connect(serviceCreateForm, SIGNAL(serviceCreateSignal(const Service&)),
            this, SLOT(addService(const Service&)));

    serviceCreateForm->setAttribute(Qt::WA_DeleteOnClose, true);
    serviceCreateForm->show();
}

void ServicesListForm::onEditButtonClicked(const QVariant& data) {
    auto* serviceViewForm = new ServiceForm(database_, *getValueFromModelData<Service>(data));
    connect(serviceViewForm, SIGNAL(serviceEditSignal(const Service&)),
            this, SLOT(editService(const Service&)));

    serviceViewForm->setAttribute(Qt::WA_DeleteOnClose, true);
    serviceViewForm->show();
}

void ServicesListForm::onDeleteButtonClicked(const QVariant& data) {
    auto value = *getValueFromModelData<Service>(data);
    database_->service->setDeletedMark(value, !value.isDeleted());
    editService(value);
}

void ServicesListForm::addService(const Service& service) {
    ui->serviceTable->appendRow(service, CreateRows::createServiceRow(service));
}

void ServicesListForm::editService(const Service& editedService) {
    ui->serviceTable->editData(editedService, CreateRows::createServiceRow(editedService));
}

void ServicesListForm::setupTableSettings() {
    ui->serviceTable->setHorizontalHeaderLabels({"Наименование", "Цена", "Длительность"});
    ui->serviceTable->setScale({4, 1, 1});
    ui->serviceTable->setMainTabLabel("Услуги");

    connect(ui->serviceTable, SIGNAL(onAddButtonClicked()),
            this, SLOT(onAddButtonClicked()));
    connect(ui->serviceTable, SIGNAL(onEditButtonClicked(const QVariant&)),
            this, SLOT(onEditButtonClicked(const QVariant&)));
    connect(ui->serviceTable, SIGNAL(onTableDoubleClicked(const QVariant&)),
            this, SLOT(onEditButtonClicked(const QVariant&)));
    connect(ui->serviceTable, SIGNAL(onDeleteButtonClicked(const QVariant&)),
            this, SLOT(onDeleteButtonClicked(const QVariant&)));
}

void ServicesListForm::fillServicesTable(const std::vector<Service>& servicesList) {
    for (const auto& service : servicesList)
        addService(service);
}
