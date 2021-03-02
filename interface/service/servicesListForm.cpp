#include "servicesListForm.h"
#include "ui_servicesListForm.h"

#include "serviceForm.h"

#include "database/databasetest.h"

#include <QSortFilterProxyModel>

#include <algorithm>

ServicesListForm::ServicesListForm(std::shared_ptr<DatabaseInterface> database,
                           QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServicesListForm)
    , database_(database)
{
    ui->setupUi(this);

    const QStringList columnNames = {"Наименование", "Цена", "Длительность"};

    tableViewModel_ = std::make_shared<QStandardItemModel>();
    tableViewModel_->setHorizontalHeaderLabels(columnNames);
    ui->tableView->setModel(tableViewModel_.get());

    std::vector<Service> servicesList;
    database_->services(servicesList);
    fillServicesTable(servicesList);
}

ServicesListForm::~ServicesListForm() {
    delete ui;
}

void ServicesListForm::resizeEvent(QResizeEvent *event) {
    static const std::vector<int> scale = {4, 1, 1};
    static const int dimension = std::accumulate(scale.begin(), scale.end(), 0);

    for (int column = 0; column < tableViewModel_->columnCount(); ++column) {
        ui->tableView->setColumnWidth(column, ui->tableView->width() * scale[column] / dimension);
    }

    QWidget::resizeEvent(event);
}

QList<QStandardItem*> ServicesListForm::createServiceRow(size_t row, const Service& service) {
    QList<QStandardItem*> lst;

    QStandardItem* name = new QStandardItem(row, 0);
    name->setText(service.name());
    name->setData(QVariant::fromValue(service), Qt::UserRole);

    QStandardItem* price = new QStandardItem(row, 1);
    price->setText(QString::number(service.price()));

    QStandardItem* duration = new QStandardItem(row, 2);
    duration->setText(service.duration().toString("hч mmм"));

    if (service.isDeprecated()) {
        QColor color = ui->tableView->palette().text().color();
        color.setAlpha(256 * 0.20);

        name->setData(QVariant::fromValue(color), Qt::ForegroundRole);
        price->setData(QVariant::fromValue(color), Qt::ForegroundRole);
        duration->setData(QVariant::fromValue(color), Qt::ForegroundRole);
    }

    lst << name << price << duration;
    return lst;
}

void ServicesListForm::fillServicesTable(const std::vector<Service>& servicesList) {
    for (const auto& service : servicesList) {
        addService(service);
    }
}

void ServicesListForm::addService(const Service& service) {
    tableViewModel_->appendRow(createServiceRow(tableViewModel_->rowCount(), service));
}

void ServicesListForm::editService(const Service& oldService, const Service& editedService) {
    for (int i = 0; i < tableViewModel_->rowCount(); ++i) {
        auto tableElement = tableViewModel_->index(i, 0);
        if (tableElement.data(Qt::UserRole).value<Service>() == oldService) {
            tableViewModel_->removeRow(i);
            tableViewModel_->insertRow(i, createServiceRow(i, editedService));
            ui->tableView->clearSelection();
            return;
        }
    }
}

void ServicesListForm::showServiceInfo(const Service& service) {
    auto* serviceViewForm = new ServiceForm(database_, service);
    connect(serviceViewForm, SIGNAL(serviceEditSignal(const Service&, const Service&)),
            this, SLOT(editService(const Service&, const Service&)));

    serviceViewForm->setAttribute(Qt::WA_DeleteOnClose, true);
    serviceViewForm->show();
}

void ServicesListForm::on_createService_clicked()
{
    auto* serviceCreateForm = new ServiceForm(database_);
    connect(serviceCreateForm, SIGNAL(serviceCreateSignal(const Service&)),
            this, SLOT(addService(const Service&)));

    serviceCreateForm->setAttribute(Qt::WA_DeleteOnClose, true);
    serviceCreateForm->show();
}

void ServicesListForm::on_tableView_doubleClicked(const QModelIndex &index) {
    const QModelIndex& firstIndex = ui->tableView->model()->index(index.row(), 0);
    showServiceInfo(firstIndex.data(Qt::UserRole).value<Service>());
}

void ServicesListForm::on_tableSettings_clicked() {
    auto* tableSettingsForm = new TableSettingsForm(ui->tableView->horizontalHeader(), this);
    tableSettingsForm->setAttribute(Qt::WA_DeleteOnClose, true);
    tableSettingsForm->show();
}

void ServicesListForm::on_searchLine_returnPressed() {
    searchInTable(ui->searchLine->text());
}

void ServicesListForm::on_searchLine_textChanged(const QString &text) {
    searchInTable(text);
}

void ServicesListForm::searchInTable(const QString& searchRequest) {
    if (tableViewModel_.get() != ui->tableView->model()) {
        delete ui->tableView->model();
    }

    auto* proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(tableViewModel_.get());
    ui->tableView->setModel(proxyModel);

    QRegExp regExp(searchRequest,
                   Qt::CaseInsensitive,
                   QRegExp::PatternSyntax(QRegExp::RegExp)
                   );
    proxyModel->setFilterKeyColumn(/*service name column*/ 0);
    proxyModel->setFilterRegExp(regExp);
}
