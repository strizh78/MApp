#pragma once

#include "file/file.h"

#include <QGraphicsScene>
#include <QGraphicsView>

class PainterView : public QGraphicsView {
public:
    PainterView(QWidget *parent = nullptr);

    void setPixmap(const FileData& fileData);
    QPixmap getPixmap();

    void clearAll();

    void setLinesColor(QColor color);
protected:
    void wheelEvent(QWheelEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QPixmap pixmap_;

    double scaleFactor_ = 1;
    QPoint drawPoint = {-1, -1};
    QPen linesPen_;
};
