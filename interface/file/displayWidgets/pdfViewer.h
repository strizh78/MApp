#pragma once

#include "viewerInterface.h"

#include <QWidget>
#include <QTemporaryFile>

#ifndef Q_OS_WINDOWS
#include <QWebEngineView>
#endif

class PdfViewer : public FileViewerInterface
        #ifndef Q_OS_WINDOWS
            , public QWebEngineView
        #else
            , public QWidget
        #endif
{
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
