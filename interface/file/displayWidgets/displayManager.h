#pragma once

#include "viewerInterface.h"

class FileDisplayManager {
public:
    FileDisplayManager(const File& file);

    FileData getData();
    void setData(const FileData& data);

    QWidget* getDisplayWidget();

private:
    enum class FileViewType {
        IMAGE,
        TEXT,
        PDF
    };

    void init();
private:
    std::map <QString, FileViewType> viewTypes;
    std::shared_ptr<FileViewerInterface> viewer_;
};
