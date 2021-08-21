#pragma once

#include "drugs/homeopathy.h"

#include "database/databaseinterface.h"

#include <QLabel>
#include <QStandardItemModel>
#include <QWidget>

#include <optional>

namespace Ui {
class HomeopathyDrugForm;
}

class HomeopathyDrugForm : public QWidget {
    Q_OBJECT

public:
    explicit HomeopathyDrugForm(std::shared_ptr<DatabaseInterface> database,
                                std::optional<homeopathy::Drug> drug = std::nullopt,
                                QWidget *parent = nullptr);
    ~HomeopathyDrugForm();

signals:
    void homeopathyDrugCreateSignal(const homeopathy::Drug& newDrug);
    void homeopathyDrugEditSignal(const homeopathy::Drug& drug);

private slots:
    void on_addDilutionsBtn_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void fillLabelFromVector(const std::vector <QString>& data);

private:
    std::optional<std::vector<QString> > isValid();
    void setEditEnabled(bool enabled);
    void init();
    void setGroupValues();

private:
    Ui::HomeopathyDrugForm *ui;
    std::shared_ptr<DatabaseInterface> database_;
    std::shared_ptr<QStandardItemModel> groupsModel_;
    std::vector<QString> dilutions_;
    homeopathy::Drug drug_;
};
