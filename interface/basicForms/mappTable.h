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
    };
    MAppTable(QWidget *parent = nullptr);
    ~MAppTable();
    void appendRow(const MAppBaseObj& data, const QList<QStandardItem*>& items);
    void editData(const MAppBaseObj& data, const QList<QStandardItem*>& list);
    void setFlag(TableSettings, bool);
    void setHorizontalHeaderLabels(const QStringList& headers);
    void setMainTabLabel(QString label);
    void setModel(QStandardItemModel* model);
    void setScale(const std::vector<int>& scale);

signals:
    void onAddButtonClicked();
    void onEditButtonClicked(const QVariant data);
    void onDeleteButtonClicked(const QVariant data);
    void onTableDoubleClicked(const QVariant data);

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

private:
    QStandardItemModel* getCurrentModel();
    QTableView* getCurrentTable();
    QStandardItemModel* modelByData(const MAppBaseObj& data);
    QTableView* tableByData(const MAppBaseObj& data);
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
    bool useBin_;
    int dimension_;
    Ui::MAppTable *ui;
};
