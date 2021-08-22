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

void AppointmentRecordForm::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    int stringsNum = 0;
    QString text = ui->fileTextEdit->toPlainText();
    int currentLen = 0;
    for (const auto& ch : text) {
        if (ch == '\n') {
            stringsNum++;
            currentLen = 0;
        } else {
            if (++currentLen >= ui->scrollArea->width() / 15) {
                stringsNum++;
                currentLen = 0;
            }
        }
    }

    ui->fileTextEdit->setGeometry(ui->fileTextEdit->geometry().x(),
                                  ui->fileTextEdit->geometry().y(),
                                  ui->scrollArea->width(),
                                  std::max(stringsNum * 17 + 15, ui->scrollArea->height()));
}

AppointmentRecordForm::~AppointmentRecordForm() {
    delete ui;
}

void AppointmentRecordForm::setEditEnabled(bool enabled) {
    ui->fileTextEdit->setEnabled(enabled);
}

void AppointmentRecordForm::setText(const QString& text) {
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
    setGeometry(this->geometry().x(), this->geometry().y(), 400, 450);
    show();

    parentWidget()->adjustSize();
}

void AppointmentRecordForm::on_returnInWindow_clicked() {
    changeButtonsVisibility(true);

    parentWidget()->layout()->addWidget(this);
    parentWidget()->adjustSize();
}

void AppointmentRecordForm::on_solutionBox_accepted() {
    on_returnInWindow_clicked();
}

void AppointmentRecordForm::changeButtonsVisibility(bool isWidget) {
    setWindowFlag(Qt::Window, !isWidget);

    ui->returnInWindow->setHidden(isWidget);
    ui->solutionBox->setHidden(isWidget);

    ui->newTabBtn->setVisible(isWidget);
}
