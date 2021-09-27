#include "databaseTest.h"

#include "serviceTestDB.h"
#include "patientTestDB.h"

#include "medicineTestDB.h"
#include "homeopathyTestDB.h"

#include "appointmentTestDB.h"
#include "eventTestDB.h"

#include "fileTestDB.h"

DatabaseTest::DatabaseTest() {
    service = new ServicesDBTest;
    patient = new PatientDBTest;

    medicine = new MedicinesDBTest;
    homeopathy = new HomeopathyDBTest;

    appointment = new AppointmentDBTest(service, patient);
    event = new EventDBTest;

    files = new FilesDBTest(appointment);
}
