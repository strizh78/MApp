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
        Drug("nameA", "nameLatA", Groups::ANIMALS, d1),
        Drug("nameB", "nameLatB", Groups::IMMATERIAL, d2),
        Drug("nameC", "nameLatC", Groups::MINERALS, d3),
        Drug("nameE", "nameLatE", Groups::ANIMALS, d4),
        Drug("nameF", "nameLatF", Groups::IMMATERIAL, d3),
        Drug("nameG", "nameLatG", Groups::MINERALS, d2),
        Drug("nameH", "nameLatH", Groups::PLANTS, d1),
        Drug("nameI", "nameLatI", Groups::ANIMALS, d1),
        Drug("nameJ", "nameLatJ", Groups::IMMATERIAL, d2),
        Drug("nameK", "nameLatK", Groups::MINERALS, d3)};

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
        *it = newDrug;
        setCodeToEdit(newDrug, oldDrug.code());
    }
}

void DatabaseTest::initMedicineDrugs() {
    using namespace medicine;

    const std::vector<ReleaseForm> relForms1 = {
        RELEASE_FORMS[0],
        RELEASE_FORMS[1],
        RELEASE_FORMS[2]};
    const std::vector<ReleaseForm> relForms2 = {
        RELEASE_FORMS[2],
        RELEASE_FORMS[5],
        RELEASE_FORMS[1]};
    const std::vector<ReleaseForm> relForms3 = {
        RELEASE_FORMS[6],
        RELEASE_FORMS[7],
        RELEASE_FORMS[8]};
    const std::vector<ReleaseForm> relForms4 = {
        RELEASE_FORMS[4],
        RELEASE_FORMS[9],
        RELEASE_FORMS[10]};
    const std::vector<QString> brands1 = {
        "brandA",
        "brandB",
        "brandC"};
    const std::vector<QString> brands2 = {
        "brandA"};
    const std::vector<QString> brands3 = {
        "brandB",
        "brandD"};
    const std::vector<QString> dosages1 = {
        "10-12, dos1",
        "12-16, dos2",
        "16+ dos3"};
    const std::vector<QString> dosages2 = {
        "1-12 мес., dos3",
        "1-10, dos4",
        "10-18+ dos5"};
    const std::vector<QString> dosages3 = {
        "2-3, dos6",
        "3-4, dos7",
        "4-16 dos8"};
    const std::vector<QString> dosages4 = {
        "dos9"};
    const std::vector<medicine::Drug> medicines = {
        Drug("actSubsA", "actSubsLatA", false, relForms1, brands1, dosages1, 3.14),
        Drug("actSubsB", "", false, relForms2, brands1, dosages1, 2.71),
        Drug("actSubsC", "actSubsLatC", false, relForms3, brands2, dosages2, 60.22),
        Drug("actSubsD", "actSubsLatD", true, relForms4, brands1, dosages1, 59.7),
        Drug("actSubsE", "actSubsLatE", false, relForms1, brands2, dosages2, 1989.1),
        Drug("actSubsF", "actSubsLatF", false, relForms2, brands3, dosages3, 9.1),
        Drug("actSubsG", "", false, relForms3, brands1, dosages1, 16.18),
        Drug("actSubsH", "actSubsLatH", false, relForms4, brands2, dosages2, 141.42),
        Drug("actSubsI", "actSubsLatI", true, relForms1, brands3, dosages3, 1202.05),
        Drug("actSubsJ", "actSubsLatJ", false, relForms1, brands3, dosages4, 1997.11),
        Drug("actSubsK", "", false, relForms2, brands2, dosages1, 379),
        Drug("actSubsL", "actSubsLatL", false, relForms3, brands1, dosages2, 1248),
        Drug("actSubsM", "actSubsLatM", false, relForms4, brands1, dosages3, 139),
        Drug("actSubsO", "", false, relForms4, brands2, dosages4, 525),
        Drug("actSubsP", "actSubsLatO", true, relForms1, brands3, dosages4, 636)};

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
        *it = newDrug;
        setCodeToEdit(newDrug, oldDrug.code());
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
        *it = editedService;
        setCodeToEdit(editedService, oldService.code());
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
        *it = editedPatient;
        setCodeToEdit(editedPatient, oldPatient.code());
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
        FullFileData(File("fileTXT_en", "txt"), QString("qwerty_123").toLocal8Bit(), parentCode),
        FullFileData(File("fileTXT_ru", "txt"), QString("кверти_123").toLocal8Bit(), parentCode),
        FullFileData(File("fileTXT_en_ru", "txt"), QString("Qwerty_кверти_123").toLocal8Bit(), parentCode),
        FullFileData(File("fileLONG_TXT_en", "txt"), longString.toLocal8Bit(), parentCode),
        FullFileData(File("filePNG", "png"),pngBytes, parentCode)
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
