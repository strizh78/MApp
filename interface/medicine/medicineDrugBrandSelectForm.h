#pragma once

#include <QLabel>
#include <QStringListModel>
#include <QWidget>

#include <memory>

namespace Ui {
class MedicineDrugBrandSelectForm;
}

class MedicineDrugBrandSelectForm : public QWidget {
    Q_OBJECT

public:
     MedicineDrugBrandSelectForm(const std::vector<QString>& brands,
                                 QLabel* label,
                                 QWidget *parent = nullptr);
    ~MedicineDrugBrandSelectForm();

signals:
    void brandsSelectedSignal(QLabel* label, const std::vector<QString>& data);

private slots:
     void on_addButton_clicked();
     void on_deleteButton_clicked();
     void on_editButton_clicked();
     void on_buttonBox_accepted();
     void on_buttonBox_rejected();

private:
    Ui::MedicineDrugBrandSelectForm *ui;
    QLabel* label_;
    std::shared_ptr<QStringListModel> listModel;
};

