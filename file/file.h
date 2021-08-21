#pragma once

#include "MAppBaseObj/mappBaseObj.h"

#include <QDateTime>
#include <QString>

#include <vector>

typedef QByteArray FileData;
const std::vector<QString>& getSupportedExtensions();

class File : public MAppBaseObj {
public:
    File() = default;
    File(const QString& name, const QString& extension);
    File(const QString& newName,
         const QString& extension,
         const QDateTime& upload,
         const QDateTime& lastEdit);

public:
    QString name;
    QString extension;
    QDateTime uploadTime;
    QDateTime lastEditTime;
};
