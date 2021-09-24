#include "editableList.h"
#include "ui_editableList.h"

#include <QLineEdit>
#include <QPushButton>

EditableList::EditableList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditableWidget)
{
    ui->setupUi(this);
    validator_ = new QRegExpValidator;

    auto* addButton = new QPushButton();
    addButton->setIcon(QIcon(":/icons/greenPlusIcon.png"));
    addButton->setMaximumSize(35, 35);

    ui->formLayout->insertRow(0, addButton, new QWidget);
    connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));

    adjustSize();
}

EditableList::~EditableList() {
    delete ui;
}

std::vector<QString> EditableList::getDataList() {
    std::vector<QString> result;

    for (auto lineEdit : findChildren<QLineEdit*>()) {
        if (!lineEdit->text().isEmpty()) {
            result.push_back(lineEdit->text());
        }
    }
    return result;
}

void EditableList::setDataList(const std::vector<QString>& data) {
    for (const auto& text : data) {
        auto [lineEdit, delButton] = createRow();
        lineEdit->setText(text);
        insertRow(lineEdit, delButton);
    }

    adjustSize();
}

void EditableList::setMinimumWidth(int minWidth) {
    minWidth_ = minWidth;
}

void EditableList::setRegExp(const QRegExp& regExp) {
    validator_ = new QRegExpValidator(regExp);
}

void EditableList::addButtonClicked() {
    auto [lineEdit, delButton] = createRow();
    insertRow(lineEdit, delButton);

    lineEdit->setFocus();
    adjustSize();
}

void EditableList::deleteButtonClicked() {
    auto* button = qobject_cast<QPushButton*>(sender());
    ui->formLayout->removeRow(button);

    adjustSize();
}

std::pair <QLineEdit*, QPushButton*> EditableList::createRow() {
    auto* lineEdit = new QLineEdit;
    auto* delButton = new QPushButton();
    delButton->setIcon(QIcon(":/icons/noIcon.png"));
    delButton->setMaximumSize(30, 30);

    lineEdit->setMinimumWidth(minWidth_);
    lineEdit->setValidator(validator_);

    connect(delButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
    return {lineEdit, delButton};
}

void EditableList::insertRow(QLineEdit* lineEdit, QPushButton* delButton) {
    ui->formLayout->insertRow((ui->formLayout->count() - 1) / 2, lineEdit, delButton);
}
