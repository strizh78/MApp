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

void Service::setName(const QString& name) {
    name_ = name;
}

float Service::price() const {
    return price_;
}

void Service::setPrice(float price) {
    price_ = price;
}

QTime Service::duration() const {
    return duration_;
}

void Service::setDuration(QTime duration) {
    duration_ = duration;
}

bool Service::isDeprecated() const {
    return isDeprecated_;
}

void Service::setDeprecated(bool deprecated) {
    isDeprecated_ = deprecated;
}
