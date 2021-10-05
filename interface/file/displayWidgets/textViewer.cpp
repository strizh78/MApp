#include "textViewer.h"

TextViewer::TextViewer(const QString& extension)
    : extension(extension)
    {}

FileData TextViewer::getData() {
    FileData data;
    data = this->toHtml().toLocal8Bit();
    return data;
}

void TextViewer::setData(const FileData& data) {
    this->setHtml(QString::fromLocal8Bit(data));
}

QWidget* TextViewer::widget() {
    return this;
}
