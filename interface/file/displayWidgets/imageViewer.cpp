#include "imageViewer.h"

#include "interface/utils.h"

#include <QBuffer>

ImageViewer::ImageViewer(const QString& extension) : extension(extension) {}

FileData ImageViewer::getData() {
    FileData data;

    auto pixmap = getPixmap();

    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, extension.toStdString().c_str());

    return data;
}

void ImageViewer::setData(const FileData& data) {
    loadFile(data);
}

QWidget* ImageViewer::widget() {
    return this;
}
