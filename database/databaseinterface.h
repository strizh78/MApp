#pragma once

#include "drugs/homeopathy.h"
#include "drugs/medicines.h"
#include "service/service.h"
#include "patient/patient.h"
#include "appointment/appointment.h"
#include "file/file.h"
#include "timetable/event.h"

#include "MAppBaseObj/mappBaseObj.h"

#include <QByteArray>

#include <vector>

class DatabaseInterface {
public:
    DatabaseInterface() = default;
    virtual ~DatabaseInterface() = default;

    virtual void homeopathyDrugs(std::vector<homeopathy::Drug>& ) = 0;
    virtual void addHomeopathyDrug(homeopathy::Drug& drug) = 0;
    virtual void editHomeopathyDrug(const homeopathy::Drug& oldDrug, homeopathy::Drug& newDrug) = 0;

    virtual void medicineDrugs(std::vector<medicine::Drug>&) = 0;
    virtual void addMedicineDrug(medicine::Drug& drug) = 0;
    virtual void editMedicineDrug(const medicine::Drug& oldDrug, medicine::Drug& newDrug) = 0;

    virtual void services(std::vector<Service>& ) = 0;
    virtual void addService(Service& ) = 0;
    virtual void editService(const Service& , Service& ) = 0;

    virtual void patients(std::vector<Patient>&) const = 0;
    virtual void addPatient(Patient&) = 0;
    virtual void editPatient(const Patient&, Patient&) = 0;

    virtual void appointments(std::vector<Appointment>&) const = 0;
    virtual void addAppointment(Appointment&) = 0;
    virtual void editAppointment(const Appointment&) = 0;

    virtual void events(std::vector<Event>&) const = 0;
    virtual void addEvent(Event&) = 0;
    virtual void editEvent(const Event&) = 0;
    
    virtual void files(std::vector<File>&) const = 0;
    virtual void addFile(File&, FileData&, int) = 0;
    virtual void editFile(const File&, File&, const FileData&) = 0;
    virtual void fileData(const File&, FileData&) = 0;
    virtual void appointmentByFile(const File&, Appointment&) = 0;
    virtual void filesByPatient(const Patient&, std::vector<File>&) = 0;
    virtual void filesByAppointment(const Appointment&, std::vector<File>&) = 0;

    void setCode(MAppBaseObj& item);
    void setCodeToEdit(MAppBaseObj& item, int code);
    void setDeletedMark(MAppBaseObj& item, bool isDeleted);

protected:
    virtual int getNextCode() = 0;
};
