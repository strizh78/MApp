#pragma once

#include "file/file.h"
#include "appointment/appointment.h"
#include "patient/patient.h"
#include "database/databaseInterface.h"
#include "interface/basicForms/mappTable.h"
#include "interface/interfaceUtils.h"

#include <QWidget>

namespace Ui {
class FilesListForm;
}

class FilesListForm : public QWidget {
    Q_OBJECT

public:
    explicit FilesListForm(QWidget *parent = nullptr);
    ~FilesListForm();

    void setupDatabase(DatabasePtr database);
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
    DatabasePtr database_;
    int parentAppointmentCode_;
    bool showFileWithAppointment_;
};
