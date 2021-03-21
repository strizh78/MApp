#include "appointmentRecordForm.h"
#include "ui_appointmentRecordForm.h"

#include <QCloseEvent>

AppointmentRecordForm::AppointmentRecordForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppointmentRecordForm)
{
    ui->setupUi(this);
    changeButtonsVisibility(/*isWidget*/ true);
    setWindowModality(Qt::WindowModality::WindowModal);
}

AppointmentRecordForm::~AppointmentRecordForm() {
    delete ui;
}

void AppointmentRecordForm::setEditEnabled(bool enabled) {
    ui->editRecordBtn->setChecked(enabled);
    ui->fileTextEdit->setEnabled(enabled);
}

void AppointmentRecordForm::setText (const QString& text) {
    ui->fileTextEdit->setText(text);
}

QString AppointmentRecordForm::getText() {
    return ui->fileTextEdit->toPlainText();
}

void AppointmentRecordForm::closeEvent(QCloseEvent* event) {
    event->setAccepted(false);
    on_returnInWindow_clicked();
}

void AppointmentRecordForm::on_newTabBtn_clicked() {
    changeButtonsVisibility(false);
    setEditEnabled(true);
    show();

    parentWidget()->adjustSize();
}

void AppointmentRecordForm::on_returnInWindow_clicked() {
    changeButtonsVisibility(true);

    parentWidget()->layout()->addWidget(this);
    parentWidget()->adjustSize();
}

void AppointmentRecordForm::on_editRecordBtn_clicked() {
    ui->fileTextEdit->setEnabled(!ui->fileTextEdit->isEnabled());
}

void AppointmentRecordForm::on_solutionBox_accepted() {
    on_returnInWindow_clicked();
    setEditEnabled(false);
}

void AppointmentRecordForm::changeButtonsVisibility(bool isWidget) {
    setWindowFlag(Qt::Window, !isWidget);

    ui->returnInWindow->setHidden(isWidget);
    ui->solutionBox->setHidden(isWidget);

    ui->newTabBtn->setVisible(isWidget);
}
