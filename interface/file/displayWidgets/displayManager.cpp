#include "displayManager.h"

#include "imageViewer.h"
#include "textViewer.h"

FileDisplayManager::FileDisplayManager(const File& file) {
    init();
    QString extension = file.extension.toUpper();

    switch(viewTypes[extension]) {
    case FileViewType::IMAGE:
        viewer_ = new ImageViewer(extension);
        break;
    case FileViewType::TEXT:
        viewer_ = new TextViewer(extension);
        break;
    }
}

FileData FileDisplayManager::getData() {
    return viewer_->getData();
}

void FileDisplayManager::setData(const FileData& data) {
    viewer_->setData(data);
}

QWidget* FileDisplayManager::getDisplayWidget() {
    return viewer_->widget();
}

void FileDisplayManager::init() {
    viewTypes["PNG"] = FileViewType::IMAGE;
    viewTypes["TXT"] = FileViewType::TEXT;
    viewTypes["JPG"] = FileViewType::IMAGE;
    viewTypes["JPEG"] = FileViewType::IMAGE;
}
