#include "homeopathyDrugListForm.h"
#include "ui_homeopathyDrugListForm.h"
#include "homeopathyDrugForm.h"

#include "interface/tableSettingsForm.h"

#include <QSortFilterProxyModel>

using namespace homeopathy;

HomeopathyDrugListForm::HomeopathyDrugListForm(std::shared_ptr<DatabaseInterface> database,
                                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeopathyDrugListForm),
    database_(database)
{
    ui->setupUi(this);
    std::vector<Drug> homeopathyList;
    database->homeopathyDrugs(homeopathyList);
    fillHomeopathyTable(homeopathyList);
}

HomeopathyDrugListForm::~HomeopathyDrugListForm() {
    delete ui;
}

void HomeopathyDrugListForm::on_addBtn_clicked() {
    auto* homeopathyDrugForm = new HomeopathyDrugForm(database_);

    connect(homeopathyDrugForm, SIGNAL(homeopathyDrugCreateSignal(const homeopathy::Drug&)),
            this, SLOT(addHomeopathyDrug(const homeopathy::Drug&)));
    homeopathyDrugForm->setAttribute(Qt::WA_DeleteOnClose, true);
    homeopathyDrugForm->show();
}

void HomeopathyDrugListForm::on_toolBtn_clicked() {
    auto* homeopathyTableSettingsForm = new TableSettingsForm(ui->homeopathyTable->horizontalHeader(), this);
    homeopathyTableSettingsForm->setAttribute(Qt::WA_DeleteOnClose, true);
    homeopathyTableSettingsForm->show();
}

void HomeopathyDrugListForm::on_searchString_textEdited(const QString &searchString) {
    searchInTable(searchString);
}

void HomeopathyDrugListForm::on_homeopathyTable_doubleClicked(const QModelIndex &index) {
    const QModelIndex& firstIndex = ui->homeopathyTable->model()->index(index.row(), 0);
    auto* homeopathyDrugForm = new HomeopathyDrugForm(database_, firstIndex.data(Qt::UserRole).value<Drug>());

    connect(homeopathyDrugForm, SIGNAL(homeopathyDrugEditSignal(const homeopathy::Drug&, const homeopathy::Drug&)),
            this, SLOT(editHomeopathyDrug(const homeopathy::Drug&, const homeopathy::Drug&)));
    homeopathyDrugForm->setAttribute(Qt::WA_DeleteOnClose, true);
    homeopathyDrugForm->show();
}

void HomeopathyDrugListForm::addHomeopathyDrug(const Drug& newDrug) {
    tableViewModel_->appendRow(createHomeopathyDrugRow(tableViewModel_->rowCount(), newDrug));
}

void HomeopathyDrugListForm::editHomeopathyDrug(const Drug& oldDrug, const Drug& editedDrug) {
    for (int i = 0; i < tableViewModel_->rowCount(); ++i) {
        auto tableElement = tableViewModel_->index(i, 0);

        if (tableElement.data(Qt::UserRole).value<Drug>() == oldDrug) {
            tableViewModel_->removeRow(i);
            tableViewModel_->insertRow(i, createHomeopathyDrugRow(i, editedDrug));
            ui->homeopathyTable->clearSelection();
            return;
        }
    }
}

void HomeopathyDrugListForm::searchInTable(const QString& searchString) {
    if (tableViewModel_.get() != ui->homeopathyTable->model()) {
        delete ui->homeopathyTable->model();
    }

    auto* proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(tableViewModel_.get());
    ui->homeopathyTable->setModel(proxyModel);

    QRegExp regExp(searchString,
                   Qt::CaseInsensitive,
                   QRegExp::PatternSyntax(QRegExp::RegExp));
    proxyModel->setFilterKeyColumn(0);
    proxyModel->setFilterRegExp(regExp);
}

void HomeopathyDrugListForm::resizeEvent(QResizeEvent* event) {
    static const std::vector<int> scale = {4, 1};
    static const int dimension = std::accumulate(scale.begin(), scale.end(), 0);
    static const int columnNumber = tableViewModel_->columnCount();
    static const int baseWidth = (ui->homeopathyTable->width() - 10 * columnNumber) / dimension;

    for (int column = 0; column < columnNumber; ++column) {
        ui->homeopathyTable->setColumnWidth(column, baseWidth * scale[column]);
    }

    QWidget::resizeEvent(event);
}

void HomeopathyDrugListForm::fillHomeopathyTable(const std::vector<homeopathy::Drug>& homeopatyList) {
    tableViewModel_ = std::make_shared<QStandardItemModel>();

    static const QStringList columnNames = {"Наименования", "Группа"};
    tableViewModel_->setHorizontalHeaderLabels(columnNames);

    for (const auto& drug : homeopathyList) {
        addHomeopathyDrug(drug);
    }

    ui->homeopathyTable->setModel(tableViewModel_.get());
}

QList<QStandardItem*> HomeopathyDrugListForm::createHomeopathyDrugRow(size_t row, const Drug& drug) {
    QList<QStandardItem*> lst;

    QStandardItem* name = new QStandardItem(row, 0);
    name->setText(drug.getFullName());
    name->setData(QVariant::fromValue(drug), Qt::UserRole);

    QStandardItem* group = new QStandardItem(row, 1);
    group->setText(groupToString(drug.group()));

    lst << name << group;
    return lst;
}
