#pragma once

#include "viewerInterface.h"

#include <QTemporaryFile>
#include <QWebEngineView>

class PdfViewer : public FileViewerInterface, public QWebEngineView {
public:
    PdfViewer(const QString& extension);

    FileData getData() override;
    void setData(const FileData& data) override;

    QWidget* widget() override;
private:
    QString extension;

    FileData fileData_;

    QTemporaryFile tmpFile_;
    QString pathToPDFjs_;
};
