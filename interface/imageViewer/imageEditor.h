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
protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::ImageEditor *ui;
    QPixmap pix;
};
