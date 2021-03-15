#include "tableSettingsForm.h"
#include "ui_tableSettingsForm.h"

#include <QCheckBox>

TableSettingsForm::TableSettingsForm(QHeaderView* headerView,
                                     QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TableSettingsForm)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Window);
    setHeaders(headerView);
}

TableSettingsForm::TableSettingsForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TableSettingsForm)
{
    ui->setupUi(this);
}

TableSettingsForm::~TableSettingsForm() {
    delete ui;
}

void TableSettingsForm::setHeaders(QHeaderView* headerView) {
    headerView_ = headerView;
    auto* model = headerView_->model();
    for (int i = 0; i < model->columnCount(); ++i) {
        addCheckBox(model->headerData(i, Qt::Horizontal).toString(), i);
    }
}

void TableSettingsForm::accept() {
    for (int i = 0; i < headerView_->model()->columnCount(); ++i) {
        auto* checkBox = findChild<QCheckBox*>("checkBox_" + QString::number(i));
        headerView_->setSectionHidden(i, !checkBox->isChecked());
    }
    close();
}

void TableSettingsForm::reject() {
    close();
}

void TableSettingsForm::addCheckBox(const QString& prefix, int number) {
    QCheckBox* checkBox = new QCheckBox(prefix);
    checkBox->setObjectName("checkBox_" + QString::number(number));
    checkBox->setChecked(!headerView_->isSectionHidden(number));
    ui->verticalLayout_2->insertWidget(number + 1, checkBox);
}
