#pragma once

#include <QTime>
#include <QString>
#include <QMetaType>

class Service
{
public:
    Service() = default;
    Service(const QString& name, float price, QTime duration, bool deprecated = false);

    QString name() const;
    float price() const;
    QTime duration() const;
    bool isDeprecated() const;

    bool operator==(const Service& other) const;
    bool isValid() const;

private:
    QString name_;
    float price_;
    QTime duration_;
    bool isDeprecated_;
};

Q_DECLARE_METATYPE( Service ); // for QVariant
