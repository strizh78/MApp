#include "imagePainter.h"
#include "ui_imagePainter.h"

#include <QResizeEvent>
#include <QGraphicsView>
#include <QtMath>
#include <QColorDialog>

namespace  {
QPixmap createColorPixmap(const QColor& color) {
    QPixmap pix(20, 20);

    QPainter painter(&pix);
    painter.setPen(color);
    painter.setBrush(color);

    painter.drawRect(pix.rect());
    return pix;
}
}

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

void ImagePainter::on_lineColor_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->lineColor->setIcon(createColorPixmap(color));

    ui->imageView->setLinesColor(color);
}

