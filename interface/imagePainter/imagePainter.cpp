#include "imagePainter.h"
#include "ui_imagePainter.h"

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

    connect(ui->penRButton, &QRadioButton::clicked, ui->imageView, [&](){ ui->imageView->changePaintMode(ImageView::DRAW); });
    connect(ui->eraserRButton, &QRadioButton::clicked, ui->imageView, [&](){ ui->imageView->changePaintMode(ImageView::ERASE); });

    connect(ui->widthSpinBox, &QSpinBox::textChanged, ui->imageView, &ImageView::setLineWidth);
    ui->penRButton->setChecked(true);
    ui->widthSpinBox->setValue(3);
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

void ImagePainter::on_colorChooseButton_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->colorChooseButton->setIcon(createColorPixmap(color));

    ui->imageView->setDrawColor(color);
}
