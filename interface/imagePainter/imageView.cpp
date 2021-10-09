#include "imageView.h"

#include <QWheelEvent>
#include <QtMath>

ImageView::ImageView(QWidget *parent)
    : QGraphicsView(parent)
{
    scaleFactor_ = 1;
}

void ImageView::setPixmap(const FileData& fileData) {
    pixmap_.loadFromData(fileData);
    scene()->addPixmap(pixmap_);

    scene()->setSceneRect(0, 0, pixmap_.width(), pixmap_.height());
}

QPixmap ImageView::getPixmap() {
    return pixmap_;
}

void ImageView::clearAll() {
    scene()->clear();
    scale (1 / scaleFactor_, 1/ scaleFactor_);
    scene()->addPixmap(pixmap_);

    scaleFactor_ = 1;
}

void ImageView::wheelEvent(QWheelEvent* event) {
    qreal factor = qPow(1.2, event->angleDelta().x() / 10.);
    scaleFactor_ *= factor;
    scale(factor, factor);
}
