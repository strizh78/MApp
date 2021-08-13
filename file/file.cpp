#include "file.h"

File::File(const QString& name, const QString& extension)
    : name_(name)
    , extension_(extension)
{
    QDateTime now(QDateTime::currentDateTime());
    uploadTime_ = now;
    lastEditTime_ = now;
}

File::File(const QString& newName,
           const QString& extension,
           const QDateTime& upload,
           const QDateTime& lastEdit)
{
    name_ = newName;
    extension_ = extension;
    uploadTime_ = upload;
    lastEditTime_ = lastEdit;
}

QString File::name() const {
    return name_;
}

QString File::extension() const {
    return extension_;
}

QString File::fullName() const {
    return name_ + "." + extension_;
}

QDateTime File::uploadTime() const {
    return uploadTime_;
}

QDateTime File::lastEditTime() const {
    return lastEditTime_;
}

const std::vector<QString>& getSupportedExtensions() {
    static const std::vector<QString> SUPPORTED_EXTENSIONS = {"Изображения (*.png *.jpg)",
                                                       "Текст (*.txt)"};
    return SUPPORTED_EXTENSIONS;
}
