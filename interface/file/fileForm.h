#pragma once

#include "database/databaseinterface.h"

#include <QWidget>

namespace Ui {
class FileForm;
}

class FileForm : public QWidget {
    Q_OBJECT

public:
    FileForm(const File& file,
             std::shared_ptr<DatabaseInterface> database,
             QWidget *parent = nullptr);
   ~FileForm();
    void showAppointment();

private slots:
    void on_name_editingFinished();
    void on_textDisplay_textChanged();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

signals:
    void fileEditSignal(const File& file);

private:
    void setData(const FileData& data);
    FileData getData();

private:
    Ui::FileForm *ui;
    std::shared_ptr<DatabaseInterface> database_;
    File file_;
    bool isModified_;
};
