#pragma once

#include "viewerInterface.h"

#include "interface/imagePainter/imagePainter.h"

class ImageViewer : public FileViewerInterface, public ImagePainter {
public:
    ImageViewer(const QString& extension);

    FileData getData() override;
    void setData(const FileData& data) override;

    QWidget* widget() override;
private:
    QString extension;
};
