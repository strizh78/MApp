#include "servicesList.h"
#include "ui_servicesList.h"

#include "serviceEdit.h"

#include "database/databasetest.h"

#include <QSortFilterProxyModel>

#include <algorithm>

ServicesList::ServicesList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServicesList)
{
    ui->setupUi(this);

    databaseInterface_ = new DatabaseTest;

    std::vector<Service> servicesList;
    databaseInterface_->services(servicesList);
    fillServicesTable(servicesList);
}

ServicesList::~ServicesList() {
    delete ui;
    delete tableSettingsForm_;
}

void ServicesList::resizeEvent(QResizeEvent *event) {
    static const std::vector<int> scale = {4, 1, 1};
    static const int dimension = std::accumulate(scale.begin(), scale.end(), 0);

    for (int column = 0; column < tableViewModel_->columnCount(); ++column) {
        ui->tableView->setColumnWidth(column, ui->tableView->width() * scale[column] / dimension);
    }

    QWidget::resizeEvent(event);
}

QList<QStandardItem*> ServicesList::createServiceRow(size_t row, const Service& service) {
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

void ServicesList::fillServicesTable(const std::vector<Service>& servicesList) {
    tableViewModel_ = new QStandardItemModel();

    static const QStringList columnNames = {"Наименование", "Цена", "Длительность"};
    tableViewModel_->setHorizontalHeaderLabels(columnNames);

    for (const auto& service : servicesList) {
        addService(service);
    }

    ui->tableView->setModel(tableViewModel_);
}

void ServicesList::addService(const Service& service) {
    tableViewModel_->appendRow(createServiceRow(tableViewModel_->rowCount(), service));
}

void ServicesList::showServiceInfo(const Service& service) {
    auto* serviceViewForm = new ServiceEdit(service);

    serviceViewForm->setAttribute(Qt::WA_DeleteOnClose, true);
    serviceViewForm->show();
}

void ServicesList::on_createService_clicked()
{
    auto* serviceCreateForm = new ServiceEdit;
    connect(serviceCreateForm, SIGNAL(serviceCreateSignal(const Service&)), this, SLOT(addService(const Service&)));

    serviceCreateForm->setAttribute(Qt::WA_DeleteOnClose, true);
    serviceCreateForm->show();
}

void ServicesList::on_selectService_clicked() {
    const auto& selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (!selectedRows.empty()) {
        showServiceInfo(selectedRows[0].data(Qt::UserRole).value<Service>());
    }
}

void ServicesList::on_tableView_doubleClicked(const QModelIndex &index) {
    const QModelIndex& firstIndex = ui->tableView->model()->index(index.row(), 0);
    showServiceInfo(firstIndex.data(Qt::UserRole).value<Service>());
}

void ServicesList::changeColumnsDisplayOption(std::vector<bool> columns) {
    for (size_t i = 0; i < columns.size(); ++i) {
        ui->tableView->horizontalHeader()->setSectionHidden(i, columns[i]);
    }
}

void ServicesList::on_tableSettings_clicked() {
    if (!tableSettingsForm_) {
        tableSettingsForm_ = new ServiceTableSettings;
    }

    connect(tableSettingsForm_, SIGNAL(signalChangeColumnsDisplay(std::vector<bool>)), this, SLOT(changeColumnsDisplayOption(std::vector<bool>)));
    tableSettingsForm_->show();
}

void ServicesList::searchInTable(const QString& searchRequest) {
    auto* proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(tableViewModel_);
    ui->tableView->setModel(proxyModel);

    QRegExp regExp(searchRequest,
                   Qt::CaseInsensitive,
                   QRegExp::PatternSyntax(QRegExp::RegExp)
                   );
    proxyModel->setFilterKeyColumn(/*service name column*/ 0);
    proxyModel->setFilterRegExp(regExp);
}

void ServicesList::on_searchLine_returnPressed() {
    searchInTable(ui->searchLine->text());
}

void ServicesList::on_searchLine_textChanged(const QString &text) {
    searchInTable(text);
}
