#pragma once

#include "file/file.h"
#include "appointment/appointment.h"
#include "patient/patient.h"
#include "database/databaseinterface.h"
#include "interface/basicForms/mappTable.h"
#include "interface/utils.h"

#include <QWidget>

namespace Ui {
class FilesListForm;
}

class FilesListForm : public QWidget {
    Q_OBJECT

public:
    explicit FilesListForm(QWidget *parent = nullptr);
    ~FilesListForm();

    void setupDatabase(std::shared_ptr<DatabaseInterface> database);
    void fillTable(const Appointment& parent);
    void fillTable(const Patient& parent);
    void fillTable();
    void setFlags(TableFlags flags);

private slots:
    void onAddButtonClicked();
    void onEditButtonClicked(const QVariant &data);
    void onDeleteButtonClicked(const QVariant &data);

    void addFile(const File& file);
    void editFile(const File& file);

private:
    void setupTableSettings();
    void fillFileTable(const std::vector<File>& fileList);

private:
    Ui::FilesListForm *ui;
    std::shared_ptr<DatabaseInterface> database_;
    int parentAppointmentCode_;
    bool showFileWithAppointment_;
};
