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
           const QDateTime& lastEdit,
           const FileData& fileData)
    : name(newName)
    , extension(extension)
    , uploadTime(upload)
    , lastEditTime(lastEdit)
    , data(fileData)
{
}

const std::vector<QString>& getSupportedExtensions() {
    static const std::vector<QString> SUPPORTED_EXTENSIONS = {"Изображения (*.png *.jpg *.jpeg)",
                                                              "Текст (*.txt)",
                                                              "PDF (*.pdf)"};
    return SUPPORTED_EXTENSIONS;
}
