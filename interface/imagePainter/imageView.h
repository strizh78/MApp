#pragma once

#include "file/file.h"

#include <QGraphicsView>

class ImageView : public QGraphicsView {
public:
    enum PaintMode {
        DRAW,
        ERASE
    };
public:
    ImageView(QWidget *parent = nullptr);

    void setPixmap(const FileData& fileData);
    QPixmap getPixmap() const;

    void clearAll();

protected:
    void wheelEvent(QWheelEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void changePaintMode(PaintMode mode);
    void setLineWidth(QString width);
    void setDrawColor(QColor color);

private:
    QPixmap pixmap_;

    double scaleFactor_;
    QPoint drawPoint_;
    int pixmapType_;

    PaintMode mode_;
    int width_;
    QColor drawColor_;
};
