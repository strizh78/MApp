#include "filesListForm.h"
#include "ui_filesListForm.h"
#include "fileForm.h"

#include "interface/utils.h"

#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QErrorMessage>

FilesListForm::FilesListForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FilesListForm)
{
    ui->setupUi(this);
    setupTableSettings();
    parentAppointmentCode_ = 0;
    showFileWithAppointment_ = true;
}

FilesListForm::~FilesListForm() {
    delete ui;
}

void FilesListForm::setupDatabase(std::shared_ptr<DatabaseInterface> database) {
    database_ = database;
}

void FilesListForm::fillTable(const Appointment& parent) {
    std::vector<File> fileList;
    database_->filesByAppointment(parent, fileList);
    fillFileTable(fileList);
    parentAppointmentCode_ = parent.code();
    showFileWithAppointment_ = false;
}

void FilesListForm::fillTable(const Patient& parent) {
    std::vector<File> fileList;
    database_->filesByPatient(parent, fileList);
    fillFileTable(fileList);
}

void FilesListForm::fillTable() {
    std::vector<File> fileList;
    database_->files(fileList);
    fillFileTable(fileList);
}

void FilesListForm::hideAddButton() {
    ui->fileTable->setFlag(MAppTable::TableSettings::UseAddButton, false);
}

void FilesListForm::onAddButtonClicked() {
    if (!parentAppointmentCode_) {
        return;
    }
    File file;
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Выбор файла",
                                                    QDir::homePath(),
                                                    toString(getSupportedExtensions(), ";; "));
    QFile qFile(fileName);

    if (!qFile.open(QIODevice::ReadOnly)) {
        QErrorMessage errorMessage(this);
        errorMessage.showMessage("Произошла ошибка при добавлении фалйа.");
        return;
    }
    QByteArray data = qFile.readAll();
    QFileInfo info(qFile);
    file = File(info.baseName(), info.suffix());
    database_->addFile(file, data, parentAppointmentCode_);
    addFile(file);
}

void FilesListForm::onEditButtonClicked(const QVariant& data){
    auto* fileForm = new FileForm(*getValueFromModelData<File>(data),
                                  database_,
                                  this);
    if (showFileWithAppointment_) {
        fileForm->showAppointment();
    }

    QObject::connect(fileForm, SIGNAL(fileEditSignal(const File&)),
                     this, SLOT(editFile(const File&)));
    fileForm->setAttribute(Qt::WA_DeleteOnClose, true);
    showAsWindowModal(fileForm);

}

void FilesListForm::onDeleteButtonClicked(const QVariant& data) {
    auto value = *getValueFromModelData<File>(data);
    database_->setDeletedMark(value, !value.isDeleted());
    editFile(value);
}

void FilesListForm::addFile(const File& file) {
    ui->fileTable->appendRow(file, CreateRows::createFileRow(file));
}

void FilesListForm::editFile(const File& file) {
    ui->fileTable->editData(file, CreateRows::createFileRow(file));
}

void FilesListForm::setupTableSettings() {
    auto* table = ui->fileTable;
    connect(table, SIGNAL(onAddButtonClicked()),
            this, SLOT(onAddButtonClicked()));
    connect(table, SIGNAL(onEditButtonClicked(const QVariant&)),
            this, SLOT(onEditButtonClicked(const QVariant&)));
    connect(table, SIGNAL(onTableDoubleClicked(const QVariant&)),
            this, SLOT(onEditButtonClicked(const QVariant&)));
    connect(table, SIGNAL(onDeleteButtonClicked(const QVariant&)),
            this, SLOT(onDeleteButtonClicked(const QVariant&)));
    table->setFlag(MAppTable::TableSettings::UseBin, false);
    table->setMainTabLabel("Файлы");
}

void FilesListForm::fillFileTable(const std::vector<File>& fileList) {
    for (const File& file : fileList) {
        addFile(file);
    }
}
