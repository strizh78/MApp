#include "editableWidget.h"
#include "ui_editableWidget.h"

#include <QPushButton>
#include <QLineEdit>

#include <iostream>

EditableWidget::EditableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditableWidget)
{
    ui->setupUi(this);
    auto* p = new QPushButton("добавить");

    ui->formLayout->insertRow(0, p, new QWidget);
    connect(p, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
}

void EditableWidget::addButtonClicked() {
    auto* l = new QLineEdit();
    auto* p = new QPushButton("удалить");

    std::cerr << ui->formLayout->count() << std::endl;
    ui->formLayout->insertRow((ui->formLayout->count() - 1) / 2, l, p);
}

EditableWidget::~EditableWidget()
{
    delete ui;
}

