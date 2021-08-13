#pragma once

#include "MAppBaseObj/mappBaseObj.h"

#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>

namespace Ui {
class MAppTable;
}

class MAppTable : public QWidget {
    Q_OBJECT

public:
    enum class TableSettings {
        UseBin,
        UseButtons,
        UseSolutionBox,
        UseAddButton
    };
    MAppTable(QWidget *parent = nullptr);
    ~MAppTable();
    void appendRow(const MAppBaseObj& data, const QList<QStandardItem*>& items);
    void editData(const MAppBaseObj& data, const QList<QStandardItem*>& list);
    void setFlag(TableSettings, bool);
    void setHorizontalHeaderLabels(const QStringList& headers);
    void setMainTabLabel(QString label);
    void setModel(const QStandardItemModel* model);
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
    void on_mainTable_doubleClicked(const QModelIndex &index);
    void on_binTable_doubleClicked(const QModelIndex &index);

    void on_solutionBox_accepted();
    void on_solutionBox_rejected();

private:
    QStandardItemModel* getCurrentModel();
    QTableView* getCurrentTable();
    QStandardItemModel* modelByData(const MAppBaseObj& data);
    QTableView* tableByData(const MAppBaseObj& data);
    QList<QStandardItem*> takeRow(const QStandardItemModel* model, int row);
    void setButtonsEnabled();
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void setEmptyModel();
    void setScale(int columnCount);
    void switchTabButtons();
    void removeRow(QStandardItemModel* model, int row);
    void setButtonsVisible(bool isVisible);
    void setBinUsage(bool useBin);
    bool editDataInTable(QStandardItemModel* firstModel,
                         QStandardItemModel* secondModel,
                         const MAppBaseObj& data,
                         const QList<QStandardItem*>& list);

private:
    std::shared_ptr<QStandardItemModel> mainTableModel;
    std::shared_ptr<QStandardItemModel> binTableModel;
    std::vector<int> scale_;
    int dimension_;

    bool useBin_;
    bool closeOnSignalEmitted_;

    Ui::MAppTable *ui;
};
