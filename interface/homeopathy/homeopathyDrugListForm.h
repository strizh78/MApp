#pragma once

#include "drugs/homeopathy.h"

#include "database/databaseinterface.h"

#include <QStandardItem>
#include <QWidget>

namespace Ui {
class HomeopathyDrugListForm;
}

class HomeopathyDrugListForm : public QWidget
{
    Q_OBJECT

public:
    explicit HomeopathyDrugListForm(std::shared_ptr<DatabaseInterface> database,
                                    QWidget *parent = nullptr);
    ~HomeopathyDrugListForm();

private slots:
    void on_addBtn_clicked();
    void on_toolBtn_clicked();
    void on_searchString_textEdited(const QString &searchString);
    void on_homeopathyTable_doubleClicked(const QModelIndex &index);

    void addHomeopathyDrug(const homeopathy::Drug& newDrug);
    void editHomeopathyDrug(const homeopathy::Drug& oldDrug, const homeopathy::Drug& editedDrug);

private:
    void searchInTable(const QString& searchString);
    void resizeEvent(QResizeEvent *event) override;
    void fillHomeopathyTable(const std::vector<homeopathy::Drug>& homeopatyList);
    QList<QStandardItem*> createHomeopathyDrugRow(size_t row, const homeopathy::Drug& drug);

private:
    Ui::HomeopathyDrugListForm *ui;
    std::shared_ptr<DatabaseInterface> database_;
    std::shared_ptr<QStandardItemModel> tableViewModel_;
};
