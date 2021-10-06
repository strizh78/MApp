#include "imageEditor.h"
#include "ui_imageEditor.h"

#include <QResizeEvent>

ImageEditor::ImageEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageEditor)
{
    ui->setupUi(this);
}

ImageEditor::~ImageEditor() {
    delete ui;
}

void ImageEditor::loadFile(const FileData& fileData) {
    pixmap_.loadFromData(fileData);
    QSize size = pixmap_.rect().size();
    if (size.width() > width() ||size.height() > height()) {
        size = {width(), height()};
    }
    resize(size);
}

QPixmap ImageEditor::getPixmap() {
    return pixmap_;
}

void ImageEditor::resizeEvent(QResizeEvent *event) {
    QPixmap temp;
    temp = pixmap_.scaled(event->size().width(),
                          event->size().height(),
                          Qt::AspectRatioMode::KeepAspectRatio);

    ui->imageLabel->setPixmap(temp);
    ui->imageLabel->resize(temp.rect().size());

    if (width() != ui->imageLabel->width() || height() != ui->imageLabel->height()) {
        resize(ui->imageLabel->width(), ui->imageLabel->height());
        return;
    }
    QWidget::resizeEvent(event);
}

