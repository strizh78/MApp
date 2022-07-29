#include "textViewer.h"

TextViewer::TextViewer(const QString& extension)
    : extension(extension)
    {}

FileData TextViewer::getData() {
    FileData data;
    data = this->toHtml().toUtf8();
    return data;
}

void TextViewer::setData(const FileData& data) {
    this->setHtml(QString::fromUtf8(data));
}

QWidget* TextViewer::widget() {
    return this;
}
