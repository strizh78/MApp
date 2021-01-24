#pragma once

#include "drugs/medicines.h"
#include "database/databaseinterface.h"

#include <QWidget>
#include <QLineEdit>

#include <optional>
#include <vector>

namespace Ui {
class MedicineDrugForm;
}

class MedicineDrugForm : public QWidget
{
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
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    void init();
    void setWidgetsSettings();
    bool isValid();
    void showWarning();

private:
    enum class OpenMode {
        CREATE,
        EDIT
    };
    Ui::MedicineDrugForm *ui;
    std::shared_ptr<DatabaseInterface> database_;
    medicine::Drug drug_;
    std::vector <medicine::ReleaseForms> releaseForms_;
    std::vector <QString> brands_;
    std::vector <Dosage> dosages_ ;
    OpenMode openMode_;
};

void setDoubleValidator(QLineEdit* lineEdit);
