#include "imageViewer.h"

#include "interface/utils.h"

#include <QBuffer>

ImageViewer::ImageViewer(const QString& extension) : extension(extension) {}

FileData ImageViewer::getData() {
    FileData data;

    this->loadFile(data);
//    QBuffer buffer(&data);
//    buffer.open(QIODevice::WriteOnly);
//    this->pixmap(Qt::ReturnByValue).save(&buffer, extension.toStdString().c_str());

    return data;
}

void ImageViewer::setData(const FileData& data) {
//    QPixmap pixMap;
//    if (pixMap.loadFromData(data)) {
//        this->setPixmap(pixMap);
//    } else {
//        ErrorLog::showItemFormWarning(this, "Не удалось открыть файл.");
//    }
    this->loadFile(data);
}

QWidget* ImageViewer::widget() {
    return this;
}
