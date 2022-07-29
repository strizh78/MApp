#pragma once

#include "database/databaseInterface.h"
#include "file/file.h"

#include "interface/file/displayWidgets/displayManager.h"

#include "interface/interfaceUtils.h"

#include <QWidget>

namespace Ui {
class FileForm;
}

class FileForm : public QWidget {
    Q_OBJECT

public:
    FileForm(const File& file,
             DatabasePtr database,
             QWidget *parent = nullptr);
   ~FileForm();
    void showAppointment();

private slots:
    void on_name_editingFinished();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

signals:
    void fileEditSignal(const File& file);

private:
    Ui::FileForm *ui;
    DatabasePtr database_;
    File file_;
    bool isModified_;

    FileDisplayManager viewer;
};
