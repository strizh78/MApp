#pragma once

#include "MAppBaseObj/mappBaseObj.h"
#include "interface/utils.h"

#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>

enum class TableFlag {
    NoBin = 0x0001,
    NoAddButton = 0x0002,
    SelectionForm = 0x0004,
};
Q_DECLARE_FLAGS(TableFlags, TableFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(TableFlags)

namespace Ui {
class MAppTable;
}

class MAppTable : public QWidget {
    Q_OBJECT

public:
    MAppTable(QWidget *parent = nullptr);
    ~MAppTable();

    void appendRow(const MAppBaseObj& data, const QList<QStandardItem*>& items);
    void editData(const MAppBaseObj& data, const QList<QStandardItem*>& items);
    void setFlags(TableFlags);
    void setMainTabLabel(QString label);
    void setHorizontalHeaderLabels(const QStringList& headers);
    void setScale(const std::vector<int>& scale);
    void setItemSelected(const MAppBaseObj& item);
    void setSelectionMode(QAbstractItemView::SelectionMode mode);

signals:
    void onAddButtonClicked();
    void onEditButtonClicked(const QVariant &data);
    void onDeleteButtonClicked(const QVariant &data);
    void onTableDoubleClicked(const QVariant &data);
    void onChooseButtonClicked(QVariant);
    void onChooseButtonClicked(std::vector<QVariant> data);

private slots:
    void on_addBtn_clicked();
    void on_editBtn_clicked();
    void on_deleteBtn_clicked();
    void on_recoverBtn_clicked();
    void on_searchString_textEdited(const QString &searchRequest);
    void on_tableSettingsBtn_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_table_doubleClicked(const QModelIndex &index);
    void on_solutionBox_accepted();
    void on_solutionBox_rejected();

private:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    void editDataInTable(const MAppBaseObj& data,
                         const QList<QStandardItem*>& list);
    QStandardItemModel* getCurrentModel();
    QTableView* getCurrentTable();
    QStandardItemModel* modelByData(const MAppBaseObj& data);
    QTableView* tableByData(const MAppBaseObj& data);
    void setButtonsEnabled();
    void setEmptyModel();
    void setScale(int columnCount);
    void switchTabButtons();
    void removeRow(QStandardItemModel* model, int row);
    void makeSelectionForm();

private:
    std::shared_ptr<QStandardItemModel> mainTableModel;
    std::shared_ptr<QStandardItemModel> binTableModel;
    std::vector<int> scale_;
    int dimension_;
    TableFlags state_;
    bool closeOnSignalEmitted_;

    Ui::MAppTable *ui;
};
