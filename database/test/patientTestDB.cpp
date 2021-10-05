#include "patientTestDB.h"
#include "interface/utils.h"

#include <QFile>

template <>
std::vector<Patient> ItemDBTestInterface<Patient>::list_ = {};
template <>
int ItemDBTestInterface<Patient>::code_ = 0;

PatientDBTest::PatientDBTest() {
    std::vector<Patient::NameInfo> names = {{"Елизавета", "Гришина", "Тимуровна"},
                                            {"Тимофей", "Никулин", "Григорьевич"},
                                            {"Никита", "Фролов", "Артурович"},
                                            {"Анна", "Попова", "Александровна"},
                                            {"Константин", "Пахомов", "Константинович"},
                                            {"Алия", "Арджеванидзе", "Даниэльевна"},
                                            {"Андрей", "Никулин", "Григорьевич"}};
    std::vector<QDate> dates = {{1963, 11, 24},
                                {1996, 8, 9},
                                {2008, 3, 8},
                                {2002, 6, 3},
                                {2021, 1, 17},
                                {2020, 5, 15},
                                {1971, 7, 13}};
    std::vector<QString> addresses = {"687940, Костромская область, город Павловский Посад, наб. Космонавтов, 96",
                                      "Смоленская область, город Ступино, спуск Славы, 97",
                                      "г. Москва, ул. Скаковая аллея, д. 15, кв. 667",
                                      "г. Дмитров, Ольховский 2-й пер, д. 165, кв. 200",
                                      "ул. Академика Лебедева (Калининский), д. 12к1, 341",
                                      "г. Дивное, ул. Пионерская, дом 55, квартира 981",
                                      "ул. Старобельская, дом 169, квартира 282"};

    std::vector<QString> phones = {"+7 (915) 715-00-85",
                                   "+7 (971) 224-40-83",
                                   "79819693396",
                                   "7 (988) 635-24-34",
                                   "+7 (935) 351-64-27",
                                   "+7 971 653 40 69",
                                   "7 926 2927499"};

    QByteArray htmlInfo;
    QFile patientFile(":qrc:/test_files/patient_file");
    if (patientFile.open(QIODevice::ReadOnly)) {
        htmlInfo = patientFile.readAll();
        patientFile.close();
    }

    std::vector<Patient> patientsList;
    for (size_t i = 0; i < names.size(); ++i) {
        Patient pat = Patient(names[i], dates[i]);
        pat.address.push_back(addresses[i]);
        pat.phones.push_back(phones[i]);

        if (i == 0) {
            pat.emails.push_back("grishina_eli@yandex.ru");
            pat.emails.push_back("grishina_eli@outlook.com");
        } else if (i == 1) {
            pat.phones.push_back("+7 922 37 37");
        }
        patientsList.push_back(pat);
    }

    for (auto patient : patientsList)
        add(patient);

    patientsList[0].additionalInfo = htmlInfo;
    update(patientsList[0]);
}
