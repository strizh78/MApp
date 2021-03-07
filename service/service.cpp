#include "service.h"

Service::Service(const QString& name, float price, QTime duration, bool deprecated)
    : name_(name)
    , price_(price)
    , duration_(duration)
    , isDeprecated_(deprecated)
{
}

QString Service::name() const {
    return name_;
}

float Service::price() const {
    return price_;
}

QTime Service::duration() const {
    return duration_;
}

bool Service::isDeprecated() const {
    return isDeprecated_;
}

bool Service::isValid() const {
    if (name_.isEmpty() ||
        price_ <= 0     ||
        duration_ <= QTime(/*hours*/ 0, /*mins*/ 0))
    {
        return false;
    }
    return true;
}
