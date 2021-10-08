#pragma once

#include "file/file.h"

#include <QGraphicsScene>
#include <QGraphicsView>

class ImageView : public QGraphicsView {
public:
    ImageView(QWidget *parent = nullptr);

    void setPixmap(const FileData& fileData);
    QPixmap getPixmap();

    void clearAll();

    void setLinesColor(QColor color);
protected:
    void wheelEvent(QWheelEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    QPixmap pixmap_;

    double scaleFactor_;
    QPoint drawPoint;
    QPen linesPen_;
};
