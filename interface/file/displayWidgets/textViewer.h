#pragma once

#include "viewerInterface.h"

#include "interface/textEditor/textEditor.h"

class TextViewer : public FileViewerInterface, public TextEditor {
public:
    TextViewer(const QString& extension);

    FileData getData() override;
    void setData(const FileData& data) override;

    QWidget* widget() override;
private:
    QString extension;
};
