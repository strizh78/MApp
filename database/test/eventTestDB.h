#pragma once

#include "itemTestInterface.h"
#include "timetable/event.h"

class EventDBTest : public ItemDBTestInterface<Event> {
public:
    EventDBTest();
};
