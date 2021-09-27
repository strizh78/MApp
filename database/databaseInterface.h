#pragma once

#include "itemDatabaseInterface.h"

class Service;
class Patient;

namespace medicine {
    class Drug;
}
namespace homeopathy {
    class Drug;
}

class Appointment;
class Event;

class DatabaseInterface;
using DatabasePtr = std::shared_ptr<DatabaseInterface>;


class DatabaseInterface {
public:
    DatabaseInterface() = default;
    virtual ~DatabaseInterface() = default;

    ItemDBInterface<Service>* service;
    ItemDBInterface<Patient>* patient;

    ItemDBInterface<medicine::Drug>* medicine;
    ItemDBInterface<homeopathy::Drug>* homeopathy;

    ItemDBInterface<Appointment>* appointment;
    ItemDBInterface<Event>* event;

    ItemDBInterface<File>* files;
};
