#include "pdfViewer.h"

#include "utils/utils.h"

PdfViewer::PdfViewer(const QString& extension)
    : extension(extension)
{
    pathToPDFjs_ = "file://" + getApplicatonDirectory() + "/pdf.js/web/viewer.html";
}

FileData PdfViewer::getData() {
    return fileData_;
}

void PdfViewer::setData(const FileData& data) {
    fileData_ = data;

    tmpFile_.open();
    tmpFile_.write(data);

    const QString pdfFileURL = QString("file://" +  tmpFile_.fileName());
#ifndef Q_OS_WINDOWS
    load(QUrl::fromUserInput(pathToPDFjs_ + QString("?file=") + pdfFileURL));
#endif
}

QWidget* PdfViewer::widget() {
    return this;
}