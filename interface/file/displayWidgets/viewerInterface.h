#pragma once

#include "file/file.h"

class FileViewerInterface {
public:
    virtual FileData getData() = 0;
    virtual void setData(const FileData& data) = 0;

    virtual QWidget* widget() = 0;
};
