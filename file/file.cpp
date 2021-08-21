#include "file.h"

File::File(const QString& name, const QString& extension)
    : name(name)
    , extension(extension)
{
    QDateTime now(QDateTime::currentDateTime());
    uploadTime = now;
    lastEditTime = now;
}

File::File(const QString& newName,
           const QString& extension,
           const QDateTime& upload,
           const QDateTime& lastEdit)
    : name(newName)
    , extension(extension)
    , uploadTime(upload)
    , lastEditTime(lastEdit)
{
}

const std::vector<QString>& getSupportedExtensions() {
    static const std::vector<QString> SUPPORTED_EXTENSIONS = {"Изображения (*.png *.jpg)",
                                                       "Текст (*.txt)"};
    return SUPPORTED_EXTENSIONS;
}
