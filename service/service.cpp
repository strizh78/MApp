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

bool Service::operator==(const Service& other) const {
    return std::abs(price_ - other.price()) < 1e-9 &&
           name_ == other.name() &&
           duration_ == other.duration() &&
           isDeprecated_ == other.isDeprecated();
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
