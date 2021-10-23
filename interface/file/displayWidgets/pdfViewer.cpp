#include "pdfViewer.h"

#include <QDir>

namespace {
QString getApplicatonDirectory() {
    QDir dir;

#ifdef Q_OS_MACOS
    dir.cd("../../..");
#endif

    return dir.absolutePath();
}
}

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
    load(QUrl::fromUserInput(pathToPDFjs_ + QString("?file=") + pdfFileURL));
}

QWidget* PdfViewer::widget() {
    return this;
}
