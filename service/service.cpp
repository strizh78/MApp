#include "service.h"

Service::Service(const QString& name, float price, QTime duration, bool deprecated)
    : name(name)
    , price(price)
    , duration(duration)
    , isDeprecated(deprecated)
{
}

bool Service::isValid() const {
    if (name.isEmpty() ||
        price <= 0     ||
        duration <= QTime(/*hours*/ 0, /*mins*/ 0))
    {
        return false;
    }
    return true;
}
