#pragma once

#include "itemTestInterface.h"
#include "drugs/medicines.h"

class MedicinesDBTest : public ItemDBTestInterface<medicine::Drug> {
public:
    MedicinesDBTest();
};
