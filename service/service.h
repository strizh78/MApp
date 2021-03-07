#pragma once

#include "MAppBaseObj/mappBaseObj.h"

#include <QTime>
#include <QString>
#include <QMetaType>

class Service : public MAppBaseObj {
public:
    Service() = default;
    Service(const QString& name, float price, QTime duration, bool deprecated = false);

    QString name() const;
    float price() const;
    QTime duration() const;
    bool isDeprecated() const;

    bool isValid() const;

private:
    QString name_;
    float price_;
    QTime duration_;
    bool isDeprecated_;
};

Q_DECLARE_METATYPE( Service ); // for QVariant
