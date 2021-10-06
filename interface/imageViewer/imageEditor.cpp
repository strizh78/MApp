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
#include <iostream>
void ImageEditor::loadFile(const FileData& fileData) {
    pix.loadFromData(fileData);
    QPixmap temp;
    temp = resizePixmap(pix, ui->imageLabel->width(), ui->imageLabel->height());

    std::cout << "1 " << width() << ' ' << height() << std::endl;
    ui->imageLabel->setPixmap(temp);
    ui->imageLabel->resize(temp.rect().size());
    ui->scrollArea->resize(temp.rect().width() + 2,
                           temp.rect().height() + 2);

    std::cout << "2 " << temp.rect().width() << ' ' << temp.rect().height() << std::endl;
    scaleFactor = 1.0;
}

void ImageEditor::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    QPixmap temp;
    temp = resizePixmap(pix, ui->imageLabel->width(), ui->imageLabel->height());

    ui->imageLabel->setPixmap(temp);
    ui->imageLabel->resize(temp.rect().size());
    ui->scrollArea->resize(temp.rect().width() + 2,
                           temp.rect().height() + 2);

    std::cout << "4 " << width() << ' ' << height() << std::endl;
}
