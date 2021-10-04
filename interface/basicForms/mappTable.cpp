#include "mappTable.h"
#include "ui_mappTable.h"

#include "drugs/medicines.h"
#include "interface/basicForms/mappTableSettingsForm.h"
#include "components/multiColumnSortFilterProxyModel/multiColumnSortFilterProxyModel.h"

#include <optional>

namespace {
const MAppBaseObj* getData(const QStandardItemModel* model, int row) {
    return model->data(model->index(row, 0), Qt::UserRole).value<const MAppBaseObj*>();
}

std::optional<QModelIndex> indexInTable(QStandardItemModel* model, const MAppBaseObj& data) {
    for (int i = 0; i < model->rowCount(); ++i) {
        if (*getData(model, i) == data) {
            return model->index(i, 0);
        }
    }
    return std::nullopt;
}

void setFocusOnRow(QTableView* table, int row) {
    QAbstractItemModel* model = table->model();

    if (model->rowCount() != 0) {
        auto index = model->index(std::min(model->rowCount() - 1, row), 0);
        table->setCurrentIndex(index);
        table->scrollTo(index);
    }
}

void setFocusOnLastRow(QTableView* table) {
    setFocusOnRow(table, table->model()->rowCount() - 1);
}
}

MAppTable::MAppTable(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MAppTable)
{
    ui->setupUi(this);
    ui->solutionBox->hide();
    setEmptyModel();
}

MAppTable::~MAppTable() {
    delete ui;
}

void MAppTable::appendRow(const MAppBaseObj& data, const QList<QStandardItem*>& items) {
    auto *model = modelByData(data);
    auto *table = tableByData(data);

    model->appendRow(items);
    setButtonsEnabled();
    setFocusOnLastRow(table);

    if (scale_.empty()) {
        setScale(items.count());
    }
}

void MAppTable::editData(const MAppBaseObj& data, const QList<QStandardItem*>& items) {
    editDataInTable(data, items);
    setButtonsEnabled();
}

void MAppTable::setFlags(TableFlags flags) {
    state_ |= flags;
    if (state_.testFlag(TableFlag::NoBin)) {
        ui->tabWidget->tabBar()->hide();
    }
    if (state_.testFlag(TableFlag::NoAddButton)) {
        ui->addBtn->hide();
    }
    if (state_.testFlag(TableFlag::SelectionForm)) {
        makeSelectionForm();
    }
}

void MAppTable::setMainTabLabel(QString label) {
    ui->tabWidget->setTabText(0, label);
}

void MAppTable::setHorizontalHeaderLabels(const QStringList& headers) {
    bool isHeadersVisible = !headers.empty();
    ui->mainTable->horizontalHeader()->setVisible(isHeadersVisible);
    ui->binTable->horizontalHeader()->setVisible(isHeadersVisible);
    mainTableModel.get()->setHorizontalHeaderLabels(headers);
    binTableModel.get()->setHorizontalHeaderLabels(headers);

    if (scale_.empty() && isHeadersVisible) {
        setScale(headers.count());
    }
}

void MAppTable::setScale(const std::vector<int>& scale){
    scale_ = scale;
    dimension_ = std::accumulate(scale_.begin(), scale_.end(), 0);
}

void MAppTable::setItemSelected(const MAppBaseObj& item) {
    auto* model = modelByData(item);
    auto* table = tableByData(item);
    auto index = indexInTable(model, item);

    if (index.has_value()) {
        table->selectRow(index->row());
    }
}

void MAppTable::setSelectionMode(QAbstractItemView::SelectionMode mode) {
    ui->mainTable->setSelectionMode(mode);
    ui->binTable->setSelectionMode(mode);
}

void MAppTable::on_addBtn_clicked() {
    emit onAddButtonClicked();
}

void MAppTable::on_editBtn_clicked() {
    QStandardItemModel* model = getCurrentModel();
    auto index = model->index(getCurrentTable()->currentIndex().row(), 0);
    emit onEditButtonClicked(model->data(index, Qt::UserRole));
}

void MAppTable::on_deleteBtn_clicked() {
    auto index = mainTableModel->index(ui->mainTable->currentIndex().row(), 0);
    emit onDeleteButtonClicked(mainTableModel->data(index, Qt::UserRole));
}

void MAppTable::on_recoverBtn_clicked() {
    auto index = binTableModel->index(ui->binTable->currentIndex().row(), 0);
    emit onDeleteButtonClicked(binTableModel->data(index, Qt::UserRole));
}

void MAppTable::on_searchString_textEdited(const QString &searchRequest) {
    QTableView* table = getCurrentTable();
    QStandardItemModel* model = getCurrentModel();

    if (table->model() != model)
        delete table->model();

    auto* proxyModel = new MultiColumnSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    table->setModel(proxyModel);

    QRegExp regExp(searchRequest,
                   Qt::CaseInsensitive,
                   QRegExp::PatternSyntax(QRegExp::RegExp));
    proxyModel->setFilterRegExp(regExp);
}

void MAppTable::on_tableSettingsBtn_clicked() {
    auto* tableSettingsForm = new MAppTableSettingsForm(ui->tabWidget, this);

    tableSettingsForm->setAttribute(Qt::WA_DeleteOnClose, true);
    tableSettingsForm->show();
}

void MAppTable::on_tabWidget_currentChanged(int index) {
    Q_UNUSED(index);
    on_searchString_textEdited(ui->searchString->text());
    switchTabButtons();
    setFocusOnRow(getCurrentTable(), 0);
}

void MAppTable::on_mainTable_doubleClicked(const QModelIndex &index) {
    QModelIndex curIndex = mainTableModel->index(index.row(), 0);
    emit onTableDoubleClicked(mainTableModel->data(curIndex, Qt::UserRole));
}

void MAppTable::on_binTable_doubleClicked(const QModelIndex &index) {
    QModelIndex curIndex = binTableModel->index(index.row(), 0);
    emit onTableDoubleClicked(binTableModel->data(curIndex, Qt::UserRole));
}

void MAppTable::on_solutionBox_accepted() {
    auto* model = getCurrentModel();
    auto* table = getCurrentTable();
    switch (table->selectionMode()) {
        case QAbstractItemView::SingleSelection:
        {
            auto index = model->index(table->currentIndex().row(), 0);
            emit onChooseButtonClicked(model->data(index, Qt::UserRole));
            break;
        }
        case QAbstractItemView::MultiSelection:
        {
            std::vector <QVariant> items;
            auto selectedItems = table->selectionModel()->selectedRows(/*column*/ 0);
            for (auto& x : selectedItems) {
                items.push_back(model->data(x, Qt::UserRole));
            }
            emit onChooseButtonClicked(items);
            break;
        }
        default:
            throw "Selection mode is not supported";
    }
}

void MAppTable::on_solutionBox_rejected() {
    close();
}

void MAppTable::resizeEvent(QResizeEvent* event) {
    if (!dimension_) {
        return;
    }

    int columnCount = mainTableModel->columnCount();

    if (scale_.empty()) {
       setScale(columnCount);
    }

    int baseWidth = (ui->mainTable->width() - 10 * columnCount) / dimension_;

    for (int column = 0; column < columnCount - 1; ++column) {
        ui->mainTable->setColumnWidth(column, baseWidth * scale_[column]);
        ui->binTable->setColumnWidth(column, baseWidth * scale_[column]);
    }

    QWidget::resizeEvent(event);
}

void MAppTable::showEvent(QShowEvent* event){
    setFocusOnRow(ui->mainTable, 0);
    setButtonsEnabled();
    switchTabButtons();
    QWidget::showEvent(event);
}

void MAppTable::editDataInTable(const MAppBaseObj& data,
                                const QList<QStandardItem*>& list)
{
    auto* modelTo = modelByData(data);
    auto* modelFrom = mainTableModel.get();
    auto index = indexInTable(modelFrom, data);

    if (!index.has_value()) {
        modelFrom = binTableModel.get();
        index = indexInTable(modelFrom, data);
    }

    if (!index.has_value()) {
        appendRow(data, list);
        return;
    }

    int row = index.value().row();
    removeRow(modelFrom, row);

    if (modelFrom == modelTo) {
        modelTo->insertRow(row, list);
        tableByData(data)->setCurrentIndex(index.value());
    }
    else
        modelTo->appendRow(list);
}

QStandardItemModel* MAppTable::getCurrentModel() {
    if (ui->tabWidget->currentIndex() == 0)
        return mainTableModel.get();
    return binTableModel.get();
}

QTableView* MAppTable::getCurrentTable() {
    if (ui->tabWidget->currentIndex() == 0)
        return ui->mainTable;
    return ui->binTable;
}

QStandardItemModel* MAppTable::modelByData(const MAppBaseObj& data) {
    if (data.isDeleted())
        return binTableModel.get();
    return mainTableModel.get();
}

QTableView* MAppTable::tableByData(const MAppBaseObj& data) {
    if (data.isDeleted())
        return ui->binTable;
    return ui->mainTable;
}

void MAppTable::setButtonsEnabled() {
    bool hasRows = mainTableModel->rowCount() > 0;

    ui->editBtn->setEnabled(hasRows);
    ui->deleteBtn->setEnabled(hasRows);

    hasRows = binTableModel->rowCount() > 0;

    ui->recoverBtn->setEnabled(hasRows);
    ui->editBtn_2->setEnabled(hasRows);
}

void MAppTable::setEmptyModel() {
    mainTableModel = std::make_shared<QStandardItemModel>();
    binTableModel = std::make_shared<QStandardItemModel>();
    ui->mainTable->setModel(mainTableModel.get());
    ui->binTable->setModel(binTableModel.get());
    setHorizontalHeaderLabels({});
    mainTableModel->setColumnCount(1);
    binTableModel->setColumnCount(1);
}

void MAppTable::setScale(int columnCount) {
    scale_ = std::vector<int>(columnCount, 1);
    dimension_ = columnCount;
}

void MAppTable::switchTabButtons() {
    bool curIndex = ui->tabWidget->currentIndex();

    ui->mainTabButtonBar->setHidden(curIndex);
    ui->binTabButtonBar->setVisible(curIndex);
}

void MAppTable::removeRow(QStandardItemModel* model, int row) {
    model->removeRow(row);
    setButtonsEnabled();
}

void MAppTable::makeSelectionForm() {
    ui->buttonBar->hide();
    ui->solutionBox->show();
}
