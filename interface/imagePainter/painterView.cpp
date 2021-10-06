#include "painterView.h"

#include <QResizeEvent>
#include <QGraphicsView>
#include <QtMath>
#include <QColorDialog>

PainterView::PainterView(QWidget *parent)
    : QGraphicsView(parent)
{
    linesPen_ = QPen();
    linesPen_.setWidth(2);

    scaleFactor_ = 1;
    drawPoint = QPoint(-1, -1);
}

void PainterView::setPixmap(const FileData& fileData) {
    pixmap_.loadFromData(fileData);
    scene()->addPixmap(pixmap_);

    scene()->setSceneRect(0, 0, pixmap_.width(), pixmap_.height());
}

QPixmap PainterView::getPixmap() {
    return pixmap_;
}

void PainterView::clearAll() {
    scene()->clear();
    scene()->addPixmap(pixmap_);

    scaleFactor_ = 1;
    drawPoint = QPoint(-1, -1);
}

void PainterView::wheelEvent(QWheelEvent* event) {
    qreal factor = qPow(1.2, event->angleDelta().x() / 240.0);
    scaleFactor_ *= factor;
    scale(factor, factor);
}

void PainterView::setLinesColor(QColor color) {
    linesPen_.setColor(color);
}

void PainterView::mouseMoveEvent(QMouseEvent *event) {
    if (event->modifiers() == Qt::CTRL) {
        if (drawPoint == QPoint(-1, -1)) {
            drawPoint = event->pos();
            return;
        }

        QLineF line(mapToScene(drawPoint),
                    mapToScene(event->pos()));
        drawPoint = event->pos();

        scene()->addLine(line, linesPen_);
        update();
    } else {
        drawPoint = QPoint(-1, -1);
    }

}
