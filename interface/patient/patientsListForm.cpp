#include "patientsListForm.h"
#include "ui_patientsListForm.h"

#include <QSortFilterProxyModel>

#include <algorithm>

PatientsListForm::PatientsListForm(std::shared_ptr<DatabaseInterface> database,
                         QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientsListForm)
    , database_(database)
{
    ui->setupUi(this);

    const QStringList columnNames = {"Фамилия И.О.", "Дата рождения", "Адрес"};

    tableViewModel_ = std::make_shared<QStandardItemModel>();
    tableViewModel_->setHorizontalHeaderLabels(columnNames);
    ui->tableView->setModel(tableViewModel_.get());

    std::vector<Patient> patientsList;
    database_->patients(patientsList);
    fillPatientsTable(patientsList);
}

PatientsListForm::~PatientsListForm() {
    delete ui;
}

void PatientsListForm::resizeEvent(QResizeEvent *event) {
    static const std::vector<int> scale = {1, 1, 3};
    static const int dimension = std::accumulate(scale.begin(), scale.end(), 0);

    for (int column = 0; column < tableViewModel_->columnCount(); ++column) {
        ui->tableView->setColumnWidth(column, ui->tableView->width() * scale[column] / dimension);
    }

    QWidget::resizeEvent(event);
}

void PatientsListForm::fillPatientsTable(const std::vector<Patient>& patientsList) {
    for (const auto& patient : patientsList) {
        addPatient(patient);
    }
}

void PatientsListForm::addPatient(const Patient& patient) {
    tableViewModel_->appendRow(createPatientRow(tableViewModel_->rowCount(), patient));
}

void PatientsListForm::editPatient(const Patient& oldPatient, const Patient& editedPatient) {
    for (int i = 0; i < tableViewModel_->rowCount(); ++i) {
        auto tableElement = tableViewModel_->index(i, 0);
        if (tableElement.data(Qt::UserRole).value<Patient>() == oldPatient) {
            tableViewModel_->removeRow(i);
            tableViewModel_->insertRow(i, createPatientRow(i, editedPatient));
            ui->tableView->clearSelection();
            return;
        }
    }
}

QList<QStandardItem*> PatientsListForm::createPatientRow(size_t row, const Patient& patient) {
    QList<QStandardItem*> lst;

    QStandardItem* initials = new QStandardItem(row, 0);
    initials->setText(patient.nameInfo().getInitials());
    initials->setData(QVariant::fromValue(patient), Qt::UserRole);

    QStandardItem* birthDate = new QStandardItem(row, 1);
    birthDate->setText(patient.birthDate().toString("d MMMM yyyy"));

    QStandardItem* address = new QStandardItem(row, 2);
    address->setText(patient.address());

    lst << initials << birthDate << address;
    return lst;
}

void PatientsListForm::on_createPatient_clicked() {
    auto* patientCreateForm = new PatientForm(database_);
    connect(patientCreateForm, SIGNAL(patientCreateSignal(const Patient&)),
            this, SLOT(addPatient(const Patient&)));

    patientCreateForm->setAttribute(Qt::WA_DeleteOnClose, true);
    patientCreateForm->show();
}

void PatientsListForm::on_tableView_doubleClicked(const QModelIndex &index) {
    const QModelIndex& firstIndex = ui->tableView->model()->index(index.row(), 0);
    showPatientInfo(firstIndex.data(Qt::UserRole).value<Patient>());
}

void PatientsListForm::showPatientInfo(const Patient& patient) {
    auto* patientViewForm = new PatientForm(database_, patient);
    connect(patientViewForm, SIGNAL(patientEditSignal(const Patient&, const Patient&)),
            this, SLOT(editPatient(const Patient&, const Patient&)));

    patientViewForm->setAttribute(Qt::WA_DeleteOnClose, true);
    patientViewForm->show();
}

void PatientsListForm::on_tableSettings_clicked() {
    auto* tableSettingsForm = new TableSettingsForm(ui->tableView->horizontalHeader(), this);
    tableSettingsForm->setAttribute(Qt::WA_DeleteOnClose, true);
    tableSettingsForm->show();
}

void PatientsListForm::on_searchLine_returnPressed() {
    searchInTable(ui->searchLine->text());
}

void PatientsListForm::on_searchLine_textChanged(const QString &text) {
    searchInTable(text);
}

void PatientsListForm::searchInTable(const QString& searchRequest) {
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
    proxyModel->setFilterKeyColumn(/*patient name column*/ 0);
    proxyModel->setFilterRegExp(regExp);
}
