#pragma once

#include "file/file.h"

#include <QWidget>

namespace Ui {
class ImageEditor;
}

class ImageEditor : public QWidget {
    Q_OBJECT

public:
    explicit ImageEditor(QWidget *parent = nullptr);
    ~ImageEditor();

    void loadFile(const FileData& fileData);
    QPixmap getPixmap();

private slots:
    void on_backToOriginal_clicked();
    void on_lineColor_clicked();

private:
    Ui::ImageEditor *ui;
};
