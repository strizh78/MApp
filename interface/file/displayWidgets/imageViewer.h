#pragma once

#include "viewerInterface.h"

#include <QLabel>

class ImageViewer : public FileViewerInterface, public QLabel {
public:
    ImageViewer(const QString& extension);

    FileData getData() override;
    void setData(const FileData& data) override;

    QWidget* widget() override;
private:
    QString extension;
};
