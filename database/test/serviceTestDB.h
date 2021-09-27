#pragma once

#include "itemTestInterface.h"
#include "service/service.h"

class ServicesDBTest : public ItemDBTestInterface<Service> {
public:
    ServicesDBTest();
};
