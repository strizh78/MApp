#include "databasetest.h"
#include "interface/utils.h"

#include <QDir>
#include <QFileInfoList>
#include <QFileDevice>

#include <algorithm>

std::vector<Appointment> DatabaseTest::appointmentsList_ = {};
std::vector<Service> DatabaseTest::servicesList_ = {};
std::vector<medicine::Drug> DatabaseTest::medicinesList_ = {};
std::vector<Patient> DatabaseTest::patientsList_ = {};
std::vector<homeopathy::Drug> DatabaseTest::homeopathyList_ = {};
std::vector<Event> DatabaseTest::eventsList_ = {};
std::vector<File> DatabaseTest::filesList_ = {};
std::vector<QByteArray> DatabaseTest::fileDataList_ = {};
std::vector<int> DatabaseTest::fileParentAppointmentCode_ = {};

int DatabaseTest::nextCode = 0;

DatabaseTest::DatabaseTest() {
    initHomeopathyDrugs();
    initMedicineDrugs();
    initPatients();
    initServices();
    initEvents();
    
    initAppointments();
    initFiles();
}

void DatabaseTest::initHomeopathyDrugs() {
    using namespace homeopathy;

    const std::vector<QString> d1 = {
        DILUTIONS[0],
        DILUTIONS[1],
        DILUTIONS[2]};
    const std::vector<QString> d2 = {
        DILUTIONS[3],
        DILUTIONS[4],
        DILUTIONS[5]};
    const std::vector<QString> d3 = {
        DILUTIONS[6],
        DILUTIONS[7],
        DILUTIONS[8]};
    const std::vector<QString> d4 = {
        DILUTIONS[0],
        DILUTIONS[3],
        DILUTIONS[4]};
    const std::vector<homeopathy::Drug> homeopathyDrugs = {
        Drug("Арсеникум альбум", "Arsenicum album", Groups::PLANTS, d1),
        Drug("Этиопс минералис", "Aethiops mineralis", Groups::MINERALS, d2),
        Drug("Ульмус фульва", "Ulmus fulva", Groups::PLANTS, d3),
        Drug("Прунус виргиниана", "Prunus virginiana", Groups::PLANTS, d4),
        Drug("Хелоне глабра", "Chelone glabra", Groups::PLANTS, d3),
        Drug("Ванадиум металликум", "Vanadium metallicum", Groups::MINERALS, d2),
        Drug("Стронтиум нитрикум", "Strontium nitricum", Groups::MINERALS, d1),
        Drug("Кониинум броматум", "Coniinum bromatum", Groups::MINERALS, d1),
        Drug("Гомерия коллина", "Homeria collina", Groups::PLANTS, d2),
        Drug("Симфитум оффицинале", "Symphytum officinale", Groups::PLANTS, d3)};

    for (auto drug : homeopathyDrugs)
        addHomeopathyDrug(drug);
}

void DatabaseTest::homeopathyDrugs(std::vector<homeopathy::Drug>& receiver) {
    receiver = homeopathyList_;
}

void DatabaseTest::addHomeopathyDrug(homeopathy::Drug& drug) {
    setCode(drug);
    homeopathyList_.push_back(drug);
}

void DatabaseTest::editHomeopathyDrug(const homeopathy::Drug& oldDrug, homeopathy::Drug& newDrug) {
    auto it = std::find(homeopathyList_.begin(), homeopathyList_.end(), oldDrug);

    if (it != homeopathyList_.end()) {
        setCodeToEdit(newDrug, oldDrug.code());
        *it = newDrug;
    }
}

void DatabaseTest::initMedicineDrugs() {
    using namespace medicine;

    const ReleaseForm capsule = RELEASE_FORMS[5];
    const ReleaseForm powder = RELEASE_FORMS[9];
    const ReleaseForm suspension = RELEASE_FORMS[10];
    const ReleaseForm tablets = RELEASE_FORMS[12];

    const std::vector<medicine::Drug> medicines = {
        Drug("", "Напроксен", "Naproxenum", true,
            {tablets},
            {"Aльгезир Ультра", "Мотрин", "Налгезин",
                  "Напроксен", "Пенталгин моно", "Тералив 275"},
            {},
            "Повышенная чувствительность к напроксену, бронхиальная астма,\
            крапивница или аллергические реакции после приема ацетисалициловой кислоты или других НПВС,\
            периоперационная боль в условиях операции аортокоронарного шунтирования.",
            125),
        Drug("", "Парацетамол", "Paracetamolum ", false,
            {tablets, suspension},
            {"Апап", "Апотель", "Детский панадол", "Ифимол",
            "Ксумапар", "Панадол", "Парацетамол", "Цефекон"},
            {Dosage("от 12 лет - 0.5 - 1г 4 раза в сутки, курс 5-7  дней"),
             Dosage("6–12 лет — 240–480 мг"),
             Dosage(1 * 12, 6 * 12, "120–240 мг"),
             Dosage("от 3 мес до 1 года — 24–120 мг до 4 раз в сутки в течение 3 дней")},
            "Гиперчувствительность, нарушение функций почек и печени, \
            алкоголизм, детский возраст (до 6 лет).",
            25),
        Drug("Мирамистин",
            "Бензилдиметил[3-(миристоиламино)пропил]аммоний хлорид моногидрат",
            "Benzyldimethyl[3-myristoilamine)-propyl]ammonium chloridi monohydratum",
            false,
            {suspension},
            {"Мирамистин"},
            {},
            "Повышенная чувствительность к действующему веществу. \
            Не рекомендуется применение препарата в форме спрея \
            для орошения горла и миндалин у детей до 3 лет ввиду \
            риска реактивного ларингоспазма.",
            200),
        Drug("Кардиомагнил ",
            "Ацетилсалициловая кислота + Магния гидроксид",
            "Acidum acetylsalicylicum + Magnesii hydroxydum",
            false,
            {tablets},
            {"Ацетилсалициловая кислота + Магния гидроксид,"
             "Кардевит", "ТромбоМАГ", "Кардиомагнил", "Магникардил"},
            {},
            "Повышенная чувствительность к ацетилсалициловой кислоте и другим НПВПС; \
            кровоизлияние в головной мозг; \
            склонность к кровотечению \
            (недостаточность витамина К, тромбоцитопения, геморрагический диатез); \
            эрозивно-язвенное поражение ЖКТ (в фазе обострения); \
            желудочно-кишечное кровотечение; \
            бронхиальная астма, индуцированная приемом салицилатов и других НПВС; \
            полное или неполное сочетание бронхиальной астмы, \
            рецидивирующего полипоза носа и околоносовых пазух \
            с непереносимостью ацетилсалициловой кислоты \
            или других НПВС, включая ингибиторы ЦОГ-2 (в т.ч. в анамнезе); \
            одновременный прием метотрексата в дозе 15 мг/нед и более; \
            тяжелая почечная недостаточность (Cl креатинина <30 мл/мин); \
            тяжелая печеночная недостаточность (класс В и С по шкале Чайлд-Пью); \
            хроническая сердечная недостаточность III и IV функционального класса по классификации NYHA; \
            беременность (I и III триместры); кормление грудью; возраст до 18 лет.",
            80),
        Drug("Арбидол", "Умифеновир", "Umifenovirum ", false,
            {tablets, capsule, powder},
            {"Арбидол", "Арбидол Максимум", "Аперфлю",
            "Алюдол", "Умифеновир"},
            {Dosage("от 6 до 12 лет — 20 мл (100 мг)"),
            Dosage("старше 12 лет и взрослым — 40 мл (200 мг) 1 раз в день в течение 12–14 дней")},
            "Повышенная чувствительность к умифеновиру; \
            детский возраст до 2–12 лет в зависимости от показания и лекарственной формы.",
            200),
        };

    for (auto drug : medicines)
        addMedicineDrug(drug);
}

void DatabaseTest::medicineDrugs(std::vector<medicine::Drug>& receiver) {
    receiver = medicinesList_;
}

void DatabaseTest::addMedicineDrug(medicine::Drug& drug) {
    setCode(drug);
    medicinesList_.push_back(drug);
}

void DatabaseTest::editMedicineDrug(const medicine::Drug& oldDrug,
                                    medicine::Drug& newDrug) {
    auto it = std::find(medicinesList_.begin(), medicinesList_.end(), oldDrug);

    if (it != medicinesList_.end()) {
        setCodeToEdit(newDrug, oldDrug.code());
        *it = newDrug;
    }
}

void DatabaseTest::initServices() {
    static const std::vector<Service> servicesList = {
        Service("Прием мануального терапевта (20 мин.)",  800, QTime(0, 20), false),
        Service("Прием мануального терапевта (30 мин.)", 1200, QTime(0, 30), false),
        Service("Прием мануального терапевта (60 мин.)", 2000, QTime(1, 00), false),

        Service("Растяжка позвоночника - дети (до 15 лет)",      300, QTime(0, 20), false),
        Service("Растяжка позвоночника - взрослые (от 15 лет)",  400, QTime(0, 30), false),
        Service("Растяжка позвоночника + массаж шеи - взрослые", 600, QTime(0, 30), false),

        Service("Mануальная терапия шейного отдела позвоночника", 1620.50, QTime(1, 0), true),
        Service("Мануальная терапия при заболеваниях суставов (плечевой, локтевой, лучезапястный)", 1495, QTime(1, 20), true),
        Service("Онлайн-консультация в зуме/телеграмме", 10000, QTime(0, 40), true),
    };

    for (auto service : servicesList)
        addService(service);
}

void DatabaseTest::services(std::vector<Service>& receiver) {
    receiver = servicesList_;
}

void DatabaseTest::addService(Service& newService) {
    setCode(newService);
    servicesList_.push_back(newService);
}

void DatabaseTest::editService(const Service& oldService, Service& editedService)
{
    auto it = std::find(servicesList_.begin(), servicesList_.end(), oldService);

    if (it != servicesList_.end()) {
        setCodeToEdit(editedService, oldService.code());
        *it = editedService;
    }
}

void DatabaseTest::initPatients() {
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

    std::vector <QString> infos = {"Телефон для связи +7 (961) 873 27 43, почта grishina_eli@yandex.ru",
                                   "[Просила не звонить после 19!]",
                                   "",
                                   "Рост 177, вес 102",
                                   "Аллергия на пенициллин и линкомицин",
                                   "Хронических заболеваний нет, операций не было",
                                   "Ана́мнез (от греч. ἀνάμνησις — воспоминание) — совокупность сведений, получаемых при медицинском обследовании путём расспроса самого обследуемого и/или знающих его лиц. Изучение анамнеза, как и расспрос в целом, не просто перечень вопросов и ответов на них. От стиля беседы врача и больного зависит та психологическая совместимость, которая во многом определяет конечную цель — облегчение состояния пациента."};

    std::vector<Patient> patientsList;
    for (size_t i = 0; i < names.size(); ++i) {
        patientsList.push_back(Patient(names[i], dates[i], addresses[i]));
    }

    for (auto patient : patientsList)
        addPatient(patient);
    patientsList_[0].additionalInfo = toString(infos, "\n\n");
    editPatient(patientsList_[0], patientsList_[0]);
}

void DatabaseTest::patients(std::vector<Patient> &receiver) const {
    receiver = patientsList_;
}

void DatabaseTest::addPatient(Patient &newPatient) {
    setCode(newPatient);
    patientsList_.push_back(newPatient);
}

void DatabaseTest::editPatient(const Patient &oldPatient, Patient &editedPatient) {
    auto it = std::find(patientsList_.begin(), patientsList_.end(), oldPatient);
    if (it != patientsList_.end()) {
        setCodeToEdit(editedPatient, oldPatient.code());
        *it = editedPatient;
    }
}

void DatabaseTest::initAppointments() {
    QDate today = QDate::currentDate();
    QDate yesterday = QDate::currentDate().addDays(-1);
    QDate tomorrow = QDate::currentDate().addDays(1);

    std::vector<Appointment> appointmentsList = {
        Appointment(patientsList_[0], servicesList_[0], QDateTime(today, {8, 10})),
        Appointment(patientsList_[4], servicesList_[1], QDateTime(today, {8, 30})),
        Appointment(patientsList_[6], servicesList_[2], QDateTime(today, {9, 00})),
        Appointment(patientsList_[1], servicesList_[1], QDateTime(today, {11, 00})),
        Appointment(patientsList_[1], servicesList_[1], QDateTime(today, {11, 30})),
        Appointment(patientsList_[3], servicesList_[5], QDateTime(today, {14, 10})),
        Appointment(patientsList_[4], servicesList_[2], QDateTime(today, {19, 00})),
        Appointment(patientsList_[5], servicesList_[4], QDateTime(today, {21, 45})),

        Appointment(patientsList_[1], servicesList_[8], QDateTime(yesterday, {8, 10})),
        Appointment(patientsList_[3], servicesList_[8], QDateTime(yesterday, {9, 45})),
        Appointment(patientsList_[0], servicesList_[1], QDateTime(yesterday, {14, 10})),
        Appointment(patientsList_[5], servicesList_[2], QDateTime(yesterday, {16, 00})),
        Appointment(patientsList_[2], servicesList_[8], QDateTime(yesterday, {20, 00})),
        Appointment(patientsList_[1], servicesList_[7], QDateTime(yesterday, {21, 45})),

        Appointment(patientsList_[2], servicesList_[0], QDateTime(tomorrow, {8, 10})),
        Appointment(patientsList_[4], servicesList_[1], QDateTime(tomorrow, {12, 45})),
        Appointment(patientsList_[3], servicesList_[3], QDateTime(tomorrow, {14, 10}))
    };

    for (auto& appointment : appointmentsList) {
        if (appointment.date.date() == yesterday)
            appointment.isConducted = true;
    }
    appointmentsList[1].isConducted = true;
    appointmentsList[7].isConducted = false;


    for (auto appointment : appointmentsList)
        addAppointment(appointment);
}

void DatabaseTest::appointments(std::vector<Appointment> &receiver) const {
    receiver = appointmentsList_;
}

void DatabaseTest::addAppointment(Appointment &newAppointment) {
    setCode(newAppointment);
    appointmentsList_.push_back(newAppointment);
}

void DatabaseTest::editAppointment(const Appointment &appointment) {
    auto it = std::find(appointmentsList_.begin(), appointmentsList_.end(), appointment);
    if (it != appointmentsList_.end()) {
        *it = appointment;
    }
}

void DatabaseTest::initFiles() {
    struct FullFileData {
        File file;
        FileData data;
        int parentCode;

        FullFileData(File _file, FileData _data, int _parentCode)
            : file(_file)
            , data(_data)
            , parentCode (_parentCode)
        {}
    };
    int parentCode = appointmentsList_[0].code();
    QString longString;

    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 100; ++j)
            longString.push_back('a' + j % 26);
        longString.push_back('\n');
    }

    QByteArray pngBytes;
    QFile pngFile(":/icons/trash.png");

    if (pngFile.open(QIODevice::ReadOnly)) {
        pngBytes = pngFile.readAll();
        pngFile.close();
    }

    std::vector<FullFileData> fullList = {
        FullFileData(File("Справка", "txt"),
                     QString("Пациент здоров, The patient is healthy").toLocal8Bit(), parentCode),
        FullFileData(File("Заключение", "txt"), longString.toLocal8Bit(), parentCode),
        FullFileData(File("Рентген", "png"), pngBytes, parentCode)
    };

    for (auto& item : fullList) {
        addFile(item.file, item.data, item.parentCode);
    }
}

void DatabaseTest::files(std::vector<File>& receiver) const {
    receiver = filesList_;
}

void DatabaseTest::addFile(File& file, FileData& data, int parentCode) {
    setCode(file);
    filesList_.push_back(file);
    fileDataList_.push_back(data);
    fileParentAppointmentCode_.push_back(parentCode);
}

void DatabaseTest::editFile(const File& oldFile, File& newFile, const FileData& data) {
    auto it = std::find(filesList_.begin(), filesList_.end(), oldFile);
    if (it == filesList_.end()) {
        return;
    }

    int idx = it - filesList_.begin();
    setCodeToEdit(newFile, oldFile.code());
    filesList_[idx] = newFile;
    fileDataList_[idx] = data;
}

void DatabaseTest::fileData(const File& file, FileData& data) {
    auto it = std::find(filesList_.begin(), filesList_.end(), file);
    if (it != filesList_.end()) {
        data = fileDataList_[it - filesList_.begin()];
    }
}

void DatabaseTest::appointmentByFile(const File& file, Appointment& appointment) {
    auto it = std::find(filesList_.begin(), filesList_.end(), file);
    if (it != filesList_.end()) {
        int code = fileParentAppointmentCode_[it - filesList_.begin()];

        for (auto app : appointmentsList_) {
            if (app.code() != code)
                continue;
            appointment = app;
            break;
        }
    }
}

void DatabaseTest::filesByPatient(const Patient& patient, std::vector<File>& receiver) {
    for (const Appointment& appointment : appointmentsList_)
        if (appointment.patient == patient)
            filesByAppointment(appointment, receiver);
}

void DatabaseTest::filesByAppointment(const Appointment& appointment, std::vector<File>& receiver) {
    int parentCode = appointment.code();
    for (int i = 0; i < filesList_.size(); ++i)
        if (fileParentAppointmentCode_[i] == parentCode)
            receiver.push_back(filesList_[i]);
}

int DatabaseTest::getNextCode() {
    return ++nextCode;
}

void DatabaseTest::initEvents() {
    QDate today = QDate::currentDate();
    QDate yesterday = QDate::currentDate().addDays(-1);
    QDate tomorrow = QDate::currentDate().addDays(1);

    std::vector<Event> eventsList = {
        Event({"Обед", QDateTime(today, {17, 20}), QTime(1, 30)}),
        Event({"Зайти в МФЦ, которое находится на щукинской (не забыть документы)",
               QDateTime(today, {15, 10}), QTime(2, 0)}),
        Event({"Забрать дочь из обучащего заведения", QDateTime(tomorrow, {9, 45}), QTime(0, 20)}),
        Event({"Обед (в кафе?)", QDateTime(tomorrow, {19, 45}), QTime(0, 30)}),
        Event({"Сходить прогуляться", QDateTime(yesterday, {21, 0}), QTime(0, 45)}),
        Event({"забрать заказ wildberries", QDateTime(yesterday, {11, 50}), QTime(1, 10)})
    };

    eventsList[0].comment = "- Суп Том Ям\n- Фрикадельки в брусничном соусе\n- Яблочный сок\n";

    for (auto event : eventsList)
        addEvent(event);
}

void DatabaseTest::events(std::vector<Event> &receiver) const {
    receiver = eventsList_;
}

void DatabaseTest::addEvent(Event &newEvent) {
    setCode(newEvent);
    eventsList_.push_back(newEvent);
}

void DatabaseTest::editEvent(const Event &event) {
    auto it = std::find(eventsList_.begin(), eventsList_.end(), event);
    if (it != eventsList_.end()) {
        *it = event;
    }
}
