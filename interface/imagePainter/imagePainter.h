#pragma once

#include "file/file.h"

#include <QWidget>

namespace Ui {
class ImagePainter;
}

class ImagePainter : public QWidget {
    Q_OBJECT

public:
    explicit ImagePainter(QWidget *parent = nullptr);
    ~ImagePainter();

    void loadFile(const FileData& fileData);
    QPixmap getPixmap();

private slots:
    void on_backToOriginal_clicked();
    void on_lineColor_clicked();

private:
    Ui::ImagePainter *ui;
};
