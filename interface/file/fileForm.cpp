#include "fileForm.h"
#include "ui_fileForm.h"

#include "interface/utils.h"
#include "appointment/appointment.h"

#include <QTabBar>
#include <QBuffer>

FileForm::FileForm(const File& file,
                   DatabasePtr database,
                   QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FileForm)
    , database_(database)
    , file_(file)
    , viewer(file)
{
    ui->setupUi(this);
    setWindowTitle(file_.name);
    ui->errorLabel->hide();
    ui->name->setText(file_.name);
    ui->extensionValue->setText(file_.extension);
    ui->uploadTimeValue->setText(file_.uploadTime.toString());
    ui->lastUpdTimeValue->setText(file_.lastEditTime.toString());
    ui->appointmentLabel->hide();

    FileData data;
    database_->files->fileData(file_, data);
    viewer.setData(data);

    ui->allLayout->addWidget(viewer.getDisplayWidget());
}

FileForm::~FileForm() {
    delete ui;
}

void FileForm::showAppointment() {
    Appointment app;
    database_->files->appointmentByFile(file_, app);
//    TODO: Make label clickable
    ui->appointmentLabel->setText(app.patient.nameInfo.getInitials() + " " + app.date.toString());
    ui->appointmentLabel->show();
}

void FileForm::on_buttonBox_accepted() {
    if (!isModified_) {
        close();
    }

    QString newName(ui->name->text());

    if (newName.isEmpty()) {
        ErrorLog::showItemFormWarning(ui->errorLabel, {ui->nameLabel->text()});
        return;
    }

    file_.name = newName;
    file_.lastEditTime = QDateTime::currentDateTime();
    database_->files->update(file_, viewer.getData());
    emit fileEditSignal(file_);

    close();
}

void FileForm::on_buttonBox_rejected() {
    close();
}

void FileForm::on_name_editingFinished() {
    isModified_ = true;
}

void FileForm::on_textDisplay_textChanged() {
    isModified_ = true;
}
