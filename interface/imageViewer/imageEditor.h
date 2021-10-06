#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <QWidget>
#include <QImageReader>
#include <QImage>
#include "file/file.h"

namespace Ui {
class ImageEditor;
}

class ImageEditor : public QWidget {
    Q_OBJECT

public:
    explicit ImageEditor(QWidget *parent = nullptr);
    ~ImageEditor();

    void loadFile(const FileData& fileData);
protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::ImageEditor *ui;
    QPixmap pix;

    double scaleFactor = 1;
};

#endif // IMAGEEDITOR_H
