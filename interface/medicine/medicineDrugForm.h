#pragma once

#include "drugs/medicines.h"
#include "database/databaseInterface.h"

#include <QLabel>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QWidget>

#include <optional>
#include <vector>

namespace Ui {
class MedicineDrugForm;
}

class MedicineDrugForm : public QWidget {
    Q_OBJECT

public:
    MedicineDrugForm(DatabasePtr database,
                     std::optional<medicine::Drug> drug = std::nullopt,
                     QWidget *parent = nullptr);
    ~MedicineDrugForm();

signals:
    void medicineDrugCreateSignal(const medicine::Drug& drug);
    void medicineDrugEditSignal(const medicine::Drug& drug);

private slots:
    void on_addBrandsBtn_clicked();
    void on_addReleaseFormsBtn_clicked();

    void on_addDosagesBtn_clicked();
    void on_deleteDosageBtn_clicked();
    void on_editDosageBtn_clicked();

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void fillLabelFromVector(QLabel* label, const std::vector <QString>& data);
    void dosageEdit(const Dosage& dosage);
    void dosageEdit(QStandardItem* item);

private:
    void init();
    void setWidgetsSettings();
    std::optional<std::vector<QString> > isValid();
    void fillDosagesList();
    void addDosage(const Dosage& dosage);
    QList<QStandardItem*> createDosageRow(size_t row, const Dosage& dosage);
    std::vector <Dosage> getDosages();
    void resizeEvent(QResizeEvent *event) override;
    void setButtonsEnabled(bool isEnabled);

private:
    Ui::MedicineDrugForm *ui;
    DatabasePtr database_;
    medicine::Drug drug_;
    std::vector <ReleaseForm> releaseForms_;
    std::vector <QString> brands_;
    std::shared_ptr<QStandardItemModel> dosagesModel_;
};
