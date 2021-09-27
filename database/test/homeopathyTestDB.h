#pragma once

#include "itemTestInterface.h"
#include "drugs/homeopathy.h"

class HomeopathyDBTest : public ItemDBTestInterface<homeopathy::Drug> {
public:
    HomeopathyDBTest();
};
