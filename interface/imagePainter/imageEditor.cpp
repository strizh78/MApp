#include "imageEditor.h"
#include "ui_imageEditor.h"

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

ImageEditor::ImageEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageEditor)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene());

    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

ImageEditor::~ImageEditor() {
    delete ui;
}

void ImageEditor::loadFile(const FileData& fileData) {
    ui->graphicsView->setPixmap(fileData);
}

QPixmap ImageEditor::getPixmap() {
    return ui->graphicsView->getPixmap();
}

void ImageEditor::on_backToOriginal_clicked() {
    ui->graphicsView->clearAll();
}

void ImageEditor::on_lineColor_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->lineColor->setIcon(createColorPixmap(color));

    ui->graphicsView->setLinesColor(color);
}

