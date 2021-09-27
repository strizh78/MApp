#pragma once

#include "itemTestInterface.h"
#include "patient/patient.h"

class PatientDBTest : public ItemDBTestInterface<Patient> {
public:
    PatientDBTest();
};
