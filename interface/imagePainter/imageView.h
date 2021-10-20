#pragma once

#include "file/file.h"

#include <QGraphicsView>

class ImageView : public QGraphicsView {
public:
    ImageView(QWidget *parent = nullptr);

    void setPixmap(const FileData& fileData);
    QPixmap getPixmap();

    void clearAll();
protected:
    void wheelEvent(QWheelEvent* event);

private:
    QPixmap pixmap_;

    double scaleFactor_;
};
