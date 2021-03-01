#include "patientTests.h"

#include "interface/patient/patientsListForm.h"

#include "ui_patientForm.h"

PatientTests::PatientTests(std::shared_ptr<DatabaseInterface> database, QObject *parent)
    : QObject(parent)
    , database_(database)
{
}

void PatientTests::createPatient() {
    Patient createdValid({"NameA", "SurnameA", "PatronymicA"},
                     QDate(1960, 1, 10),
                     "City1, Street1, 4, 18");
    assertCreatePatient(createdValid, /*valid*/ true, "create base valid patient");

    Patient createdNotValid1({"", "SurnameB", "PatronymicB"},
                     QDate(1960, 1, 10),
                     "City1, Street1, 4, 18");
    assertCreatePatient(createdNotValid1, /*valid*/ false, "create invalid name patient");

    Patient createdNotValid2({"NameC", "", "PatronymicC"},
                             QDate(1960, 1, 10),
                             "City1, Street1, 4, 18");
    assertCreatePatient(createdNotValid2, /*valid*/ false, "create invalid surname patient");

    Patient createdNotValid3({"NameD", "SurnameD", "PatronymicD"},
                             QDate(1960, 1, 10),
                             "");
    assertCreatePatient(createdNotValid3, /*valid*/ false, "create invalid address patient");

    Patient createdValidWithInfo({"NameE", "SurnameE", "PatronymicE"},
                             QDate(1960, 1, 10),
                             "City1, Street1, 4, 18");
    const QHash<QString, QString> additionalInfo = {{"key11", "value1"},
                                                    {"key21", "1ч 45m"},
                                                    {"key32", "дата: 17.02.1999"},
                                                    {"key45", "separators .,/\{}@#$%^&*()[]"},
                                                    {"key00", "0.0007"}};
    createdValidWithInfo.setAdditionalInfo(additionalInfo);
    assertCreatePatient(createdValidWithInfo, /*valid*/ true, "create patient with additional info");
}

void PatientTests::assertCreatePatient(const Patient& patient, bool valid, const std::string& messageWhat) {
    static const std::string where = "create patient test";

    PatientForm form(database_);

    setPatientFormFields(form, patient);
    form.on_solutionBox_accepted();

    std::vector<Patient> currentPatients;
    database_->patients(currentPatients);

    bool createdExists = std::find(currentPatients.begin(), currentPatients.end(), patient) != currentPatients.end();
    QTEST_ASSERT_X(createdExists == valid, where.c_str(), messageWhat.c_str());
}

void PatientTests::setPatientFormFields(PatientForm& form, const Patient& patient) {
    form.ui->nameEdit->setText(patient.nameInfo().getFullName());
    form.ui->dateEdit->setDate(patient.birthDate());
    form.ui->addressEdit->setText(patient.address());

    form.infoViewModel_->removeRows(0, form.infoViewModel_->rowCount());

    auto keys = patient.additionalInfo().keys();
    for (auto& key : keys) {
        QList<QStandardItem*> lst;
        auto* keyItem = new QStandardItem(key);
        auto* valueItem = new QStandardItem(patient.additionalInfo()[key]);
        lst << keyItem << valueItem;
        form.infoViewModel_->appendRow(lst);
    }
}

void PatientTests::editPatients() {
    // TODO spkhaykova@: научиться проходить тесты с изменением фамилии или имени на пустое (сейчас не проходит, ибо невозможно отличить пустое имя от пустого отчества)
    Patient basePatient({"NameF", "SurnameF", "PatronymicF"},
                        QDate(1960, 1, 10),
                        "City1, Street1, 4, 18");
    const QHash<QString, QString> additionalInfo = {{"key1", "value1"},
                                                    {"key2", "1ч 45m"},
                                                    {"key3", "дата: 17.02.1999"},
                                                    {"key4", "long value: long long long long int: 2183891739871837817398718937892173987218973"},
                                                    {"key5", "2.73"}};
    basePatient.setAdditionalInfo(additionalInfo);
    database_->addPatient(basePatient);

    assertModifyPatient(basePatient, basePatient, /*valid*/ true, "modify patient without changes");

    Patient editedInvalid3 = basePatient;
    editedInvalid3.setAddress("");
    assertModifyPatient(basePatient, editedInvalid3, /*valid*/ false, "modify patient address invalid");

    Patient editedValid5 = basePatient;
    const QHash<QString, QString> additionalInfoNew = {{"key1", "value1"},
                                                        {"key2", "1ч 45m"},
                                                        {"key4", "long value: long long long long int: 2183891739871837817398718937892173987218973"},
                                                        {"key6", "new value added by modify patient test"}};
    editedValid5.setAdditionalInfo(additionalInfoNew);
    assertModifyPatient(basePatient, editedValid5, /*valid*/ true, "modify patient additional info");
    basePatient = editedValid5;

    Patient editedValid6({"NameG", "SurnameG", "PatronymicG"},
                          QDate(1999, 11, 11),
                          "new address");
    editedValid6.setAdditionalInfo(additionalInfoNew);
    assertModifyPatient(basePatient, editedValid6, /*valid*/ true, "modify all patient fields");
    basePatient = editedValid6;

    Patient editedValid7 = editedValid6;
    editedValid7.setNameInfo({"NameH", "SurnameH", ""});
    assertModifyPatient(basePatient, editedValid7, /*valid*/ true, "modify patient empty patronimic");
}

void PatientTests::assertModifyPatient(const Patient& patient, const Patient& edited, bool valid, const std::string& messageWhat) {
    static const std::string where = "modify patient test";
    static const std::string whatPartOld = ": old patient existing";
    static const std::string whatPartNew = ": new patient existing";

    PatientForm form(database_, patient);

    setPatientFormFields(form, edited);
    form.on_solutionBox_accepted();

    std::vector<Patient> currentPatients;
    database_->patients(currentPatients);
    bool createdExists = std::find(currentPatients.begin(), currentPatients.end(), patient) != currentPatients.end();
    bool editedExists = std::find(currentPatients.begin(), currentPatients.end(), edited) != currentPatients.end();

    if (patient == edited) {
        QTEST_ASSERT_X(createdExists == valid, where.c_str(), (messageWhat + whatPartOld).c_str());
        QTEST_ASSERT_X(editedExists == valid, where.c_str(), (messageWhat + whatPartNew).c_str());
        return;
    }

    QTEST_ASSERT_X(createdExists == !valid, where.c_str(), (messageWhat + whatPartOld).c_str());
    QTEST_ASSERT_X(editedExists == valid, where.c_str(), (messageWhat + whatPartNew).c_str());
}

void PatientTests::listPatients() {
    const std::string where = "patients list test";
    PatientsListForm listForm(database_);

    std::vector<Patient> currentPatients;
    database_->patients(currentPatients);

    QTEST_ASSERT_X(listForm.tableViewModel_->rowCount() == (int) currentPatients.size(), where.c_str(), "table size != db patients size");
    for (size_t i = 0; i < currentPatients.size(); ++i) {
        auto index = listForm.tableViewModel_->index(i, 0);
        QTEST_ASSERT_X(currentPatients[i] == index.data(Qt::UserRole).value<Patient>(), where.c_str(), "table row UserData != real patient info");
        QTEST_ASSERT_X(currentPatients[i].nameInfo().getInitials() == index.data().value<QString>(), where.c_str(), "table row name text assertion failed");

        index = listForm.tableViewModel_->index(i, 1);
        QTEST_ASSERT_X(currentPatients[i].birthDate().toString("d MMMM yyyy") == index.data().value<QString>(), where.c_str(), "table row date text assertion failed");

        index = listForm.tableViewModel_->index(i, 2);
        QTEST_ASSERT_X(currentPatients[i].address() == index.data().value<QString>(), where.c_str(), "table row address text assertion failed");
    }
}
