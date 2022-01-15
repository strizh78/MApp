#include "imageView.h"

#include <QGraphicsItem>
#include <QWheelEvent>
#include <QtMath>

static const QPoint NO_DRAWING_POINT = QPoint(-1, -1);

ImageView::ImageView(QWidget *parent)
    : QGraphicsView(parent)
{
    scaleFactor_ = 1;
    drawPoint_ = NO_DRAWING_POINT;
    mode_ = DRAW;
}

void ImageView::setPixmap(const FileData& fileData) {
    pixmap_.loadFromData(fileData);
    auto* pixmapItem = scene()->addPixmap(pixmap_);
    pixmapType_ = pixmapItem->type();

    scene()->setSceneRect(0, 0, pixmap_.width(), pixmap_.height());
}

QPixmap ImageView::getPixmap() const {
    return pixmap_;
}

void ImageView::clearAll() {
    scene()->clear();
    scale (1 / scaleFactor_, 1/ scaleFactor_);
    scene()->addPixmap(pixmap_);

    scaleFactor_ = 1;
    drawPoint_ = NO_DRAWING_POINT;
}

void ImageView::changePaintMode(PaintMode mode) {
    mode_ = mode;
}

void ImageView::setLineWidth(QString width) {
    width_ = width.toInt();
}

void ImageView::setDrawColor(QColor color) {
    drawColor_ = color;
}

void ImageView::wheelEvent(QWheelEvent* event) {
    qreal factor = qPow(1.2, event->angleDelta().x() / 10.);
    scaleFactor_ *= factor;
    scale(factor, factor);
}

void ImageView::mouseMoveEvent(QMouseEvent *event) {
    if (mode_ == DRAW) {
        if (drawPoint_ == NO_DRAWING_POINT) {
            drawPoint_ = event->pos();
            return;
        }
        QLineF line(mapToScene(drawPoint_),
                    mapToScene(event->pos()));
        scene()->addLine(line, QPen(drawColor_, width_));

        drawPoint_ = event->pos();
    }else if (mode_ == ERASE) {
        QPointF point = mapToScene(event->pos());
        double halfWidth = width_ / 2.;
        QRectF eraseRect(point.x() - halfWidth, point.y() + halfWidth, halfWidth, halfWidth);

        foreach(auto& item, scene()->items(eraseRect)) {
            if (item->type() != pixmapType_) {
                scene()->removeItem(item);
            }
        }
    }
    QWidget::mouseMoveEvent(event);
}

void ImageView::mouseReleaseEvent(QMouseEvent *event) {
    drawPoint_ = NO_DRAWING_POINT;
    QWidget::mouseReleaseEvent(event);
}
