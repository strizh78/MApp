#pragma once

#include "viewerInterface.h"

#include <QTextEdit>

class TextViewer : public FileViewerInterface, public QTextEdit {
public:
    TextViewer(const QString& extension);

    FileData getData() override;
    void setData(const FileData& data) override;

    QWidget* widget() override;
private:
    QString extension;
};
