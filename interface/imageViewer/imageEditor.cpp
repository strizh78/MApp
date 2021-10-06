#include "imageEditor.h"
#include "ui_imageEditor.h"

#include <QColorSpace>

ImageEditor::ImageEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageEditor)
{
    ui->setupUi(this);
}

ImageEditor::~ImageEditor() {
    delete ui;
}

QPixmap resizePixmap(const QPixmap& pix, int w, int h) {
    QPixmap temp;
    temp = pix.scaled(w, h, Qt::AspectRatioMode::KeepAspectRatio);
    return temp;
}

void ImageEditor::loadFile(const FileData& fileData) {
    pix.loadFromData(fileData);
    QPixmap temp;
    temp = resizePixmap(pix, ui->imageLabel->width(), ui->imageLabel->height());

    ui->imageLabel->setPixmap(temp);
    ui->imageLabel->resize(ui->imageLabel->pixmap(Qt::ReturnByValue).rect().size());
    ui->scrollArea->resize(ui->imageLabel->pixmap(Qt::ReturnByValue).rect().size());
    this->resize(ui->imageLabel->pixmap(Qt::ReturnByValue).rect().size());
    scaleFactor = 1.0;
}

void ImageEditor::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    ui->imageLabel->resize(width(), height());

    QPixmap temp;
    temp = resizePixmap(pix, ui->imageLabel->width(), ui->imageLabel->height());

    ui->imageLabel->setPixmap(temp);
    ui->imageLabel->resize(ui->imageLabel->pixmap(Qt::ReturnByValue).rect().size());
    ui->scrollArea->resize(ui->imageLabel->pixmap(Qt::ReturnByValue).rect().size());
    this->resize(ui->imageLabel->pixmap(Qt::ReturnByValue).rect().size());
}
