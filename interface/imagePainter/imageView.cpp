#include "imageView.h"

#include <QResizeEvent>
#include <QGraphicsView>
#include <QtMath>
#include <QColorDialog>

static const QPoint NO_DRAWING_POINT = QPoint(-1, -1);

ImageView::ImageView(QWidget *parent)
    : QGraphicsView(parent)
{
    linesPen_ = QPen();
    linesPen_.setWidth(2);

    scaleFactor_ = 1;
    drawPoint = NO_DRAWING_POINT;
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
    scale(1. / scaleFactor_, 1. / scaleFactor_);

    scene()->clear();
    scene()->addPixmap(pixmap_);

    scaleFactor_ = 1;
    drawPoint = NO_DRAWING_POINT;
}

void ImageView::setLinesColor(QColor color) {
    linesPen_.setColor(color);
}

void ImageView::wheelEvent(QWheelEvent* event) {
    qreal factor = qPow(1.2, event->angleDelta().x() / 10.);
    scaleFactor_ *= factor;
    scale(factor, factor);
}

void ImageView::mouseMoveEvent(QMouseEvent *event) {
    if (event->modifiers() == Qt::CTRL) {
        if (drawPoint == NO_DRAWING_POINT) {
            drawPoint = event->pos();
            return;
        }

        QLineF line(mapToScene(drawPoint),
                    mapToScene(event->pos()));
        drawPoint = event->pos();

        scene()->addLine(line, linesPen_);
    } else {
        drawPoint = QPoint(-1, -1);
    }
}
