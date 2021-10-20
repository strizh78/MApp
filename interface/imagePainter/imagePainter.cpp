#include "imagePainter.h"
#include "ui_imagePainter.h"

ImagePainter::ImagePainter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImagePainter)
{
    ui->setupUi(this);
    ui->imageView->setScene(new QGraphicsScene());
}

ImagePainter::~ImagePainter() {
    delete ui;
}

void ImagePainter::loadFile(const FileData& fileData) {
    ui->imageView->setPixmap(fileData);
}

QPixmap ImagePainter::getPixmap() {
    return ui->imageView->getPixmap();
}

void ImagePainter::on_backToOriginal_clicked() {
    ui->imageView->clearAll();
}
