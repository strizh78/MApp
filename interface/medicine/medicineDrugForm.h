#pragma once

#include "drugs/medicines.h"
#include "database/databaseinterface.h"

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QStandardItemModel>

#include <optional>
#include <vector>

namespace Ui {
class MedicineDrugForm;
}

class MedicineDrugForm : public QWidget {
    Q_OBJECT

public:
    MedicineDrugForm(std::shared_ptr<DatabaseInterface> database,
                     std::optional<medicine::Drug> drug = std::nullopt,
                     QWidget *parent = nullptr);
    ~MedicineDrugForm();

signals:
    void medicineDrugCreateSignal(const medicine::Drug& newDrug);
    void medicineDrugEditSignal(const medicine::Drug& oldDrug,
                                const medicine::Drug& editedDrug);

private slots:
    void on_addBrandsBtn_clicked();
    void on_addReleaseFormsBtn_clicked();

    void on_addDosagesBtn_clicked();
    void on_deleteDosageBtn_clicked();
    void on_editDosageBtn_clicked();

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void fillLabelFromVector(QLabel* label, const std::vector <QString>& data);

private:
    void init();
    void setWidgetsSettings();
    std::pair<bool, std::vector<QString>> isValid();
    void fillDosagesList();
    void addDosage(const Dosage& dosage = "");
    QList<QStandardItem*> createDosageRow(size_t row, const Dosage& dosage);
    std::vector <Dosage> getDosages();
    void resizeEvent(QResizeEvent *event) override;

private:
    enum class OpenMode {
        CREATE,
        EDIT
    };
    Ui::MedicineDrugForm *ui;
    std::shared_ptr<DatabaseInterface> database_;
    medicine::Drug drug_;
    std::vector <ReleaseForm> releaseForms_;
    std::vector <QString> brands_;
    std::shared_ptr<QStandardItemModel> dosagesModel_;
    OpenMode openMode_;
};
