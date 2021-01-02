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
    void setName(const QString& name);

    float price() const;
    void setPrice(float price);

    QTime duration() const;
    void setDuration(QTime duration);

    bool isDeprecated() const;
    void setDeprecated(bool deprecated);

private:
    QString name_;
    float price_;
    QTime duration_;
    bool isDeprecated_;
};

Q_DECLARE_METATYPE( Service ); // for QVariant
