#include "fileForm.h"
#include "ui_fileForm.h"

#include "interface/utils.h"
#include "appointment/appointment.h"

#include <QTabBar>
#include <QBuffer>

FileForm::FileForm(const File& file,
                   std::shared_ptr<DatabaseInterface> database,
                   QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FileForm)
    , database_(database)
    , file_(file)
{
    ui->setupUi(this);
    setWindowTitle(file_.name());
    ui->errorLabel->hide();
    ui->name->setText(file_.name());
    ui->extensionValue->setText(file_.extension());
    ui->uploadTimeValue->setText(file_.uploadTime().toString());
    ui->lastUpdTimeValue->setText(file_.lastEditTime().toString());
    ui->tabWidget->tabBar()->hide();
    ui->appointmentLabel->hide();

    FileData data;
    database_->fileData(file_, data);
    setData(data);
}

FileForm::~FileForm() {
    delete ui;
}

void FileForm::showAppointment() {
    Appointment app;
    database_->appointmentByFile(file_, app);
//    TODO: Make label clickable
    ui->appointmentLabel->setText(app.patient.nameInfo().getInitials() + " " + app.date.toString());
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

    File newFile = File(newName,
                        file_.extension(),
                        file_.uploadTime(),
                        QDateTime::currentDateTime());
    database_->editFile(file_, newFile, getData());
    emit fileEditSignal(newFile);
    close();
}

void FileForm::on_buttonBox_rejected() {
    close();
}

void FileForm::setData(const FileData& data) {
    QString ext = file_.extension();

    if (ext == "txt") {
        ui->textDisplay->setText(QString::fromLocal8Bit(data));
        ui->tabWidget->setCurrentIndex(0);
    }
    else if (ext == "png" || ext == "jpg") {
        QPixmap pixMap;

        if (pixMap.loadFromData(data)) {
            ui->pngDisplay->setPixmap(pixMap);
            ui->tabWidget->setCurrentIndex(1);
        }
        else {
            ErrorLog::showItemFormWarning(ui->errorLabel, "Не удалось открыть файл.");
        }
    }
    ui->tabWidget->setTabVisible(ui->tabWidget->currentIndex(), true);
}

FileData FileForm::getData() {
    FileData data;
    switch (ui->tabWidget->currentIndex()) {
    case 0:
        data = ui->textDisplay->toPlainText().toLocal8Bit();
        break;
    case 1: {
        QBuffer buffer(&data);
        buffer.open(QIODevice::WriteOnly);
        const char* upperExt = file_.extension().toUpper().toStdString().c_str();
        ui->pngDisplay->pixmap(Qt::ReturnByValue).save(&buffer, upperExt);
        break;
    }
    }
    return data;
}

void FileForm::on_name_editingFinished() {
    isModified_ = true;
}

void FileForm::on_textDisplay_textChanged() {
    isModified_ = true;
}
