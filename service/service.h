#pragma once

#include "MAppBaseObj/mappBaseObj.h"

#include <QTime>
#include <QString>
#include <QMetaType>

class Service : public MAppBaseObj {
public:
    Service() = default;
    Service(const QString& name, float price, QTime duration, bool deprecated = false);

    bool isValid() const;

public:
    QString name;
    float price;
    QTime duration;
    bool isDeprecated;
};

Q_DECLARE_METATYPE( Service ); // for QVariant
