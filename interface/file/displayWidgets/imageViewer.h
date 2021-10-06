#pragma once

#include "viewerInterface.h"

#include "interface/imageViewer/imageEditor.h"
#include <QLabel>

class ImageViewer : public FileViewerInterface, public ImageEditor {
public:
    ImageViewer(const QString& extension);

    FileData getData() override;
    void setData(const FileData& data) override;

    QWidget* widget() override;
private:
    QString extension;
};
