#include "medicineDrugBrandSelectForm.h"
#include "ui_medicineDrugBrandSelectForm.h"

MedicineDrugBrandSelectForm::MedicineDrugBrandSelectForm(const std::vector<QString>& brands,
                                                         QLabel* label,
                                                         QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::MedicineDrugBrandSelectForm)
    , label_(label)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    QStringList list;

    for (QString brand : brands)
        list.append(brand);

    listModel = std::make_shared<QStringListModel>();
    listModel->setStringList(list);
    ui->listView->setModel(listModel.get());
}

MedicineDrugBrandSelectForm::~MedicineDrugBrandSelectForm() {
    delete ui;
}

void MedicineDrugBrandSelectForm::on_addButton_clicked() {
    int row = listModel->rowCount();
    listModel->insertRows(row, 1);
    QModelIndex index = listModel->index(row);
    ui->listView->setCurrentIndex(index);
    ui->listView->edit(index);
}

void MedicineDrugBrandSelectForm::on_deleteButton_clicked() {
    listModel->removeRows(ui->listView->currentIndex().row(),1);
}

void MedicineDrugBrandSelectForm::on_editButton_clicked() {
    ui->listView->edit(ui->listView->currentIndex());
}

void MedicineDrugBrandSelectForm::on_buttonBox_accepted() {

    std::vector<QString> brands;
    for (int rowId = 0; rowId < listModel->rowCount(); ++rowId) {
        auto index = listModel.get()->index(rowId);
        QString data = listModel.get()->data(index).toString();

        if (!data.isEmpty())
            brands.push_back(data);
    }
    emit brandsSelectedSignal(label_, brands);
}

void MedicineDrugBrandSelectForm::on_buttonBox_rejected() {
    close();
}
