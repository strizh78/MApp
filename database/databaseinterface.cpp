#include "databaseinterface.h"

void DatabaseInterface::setCode(MAppBaseObj& item) {
    item.setCode(getNextCode());
}

void DatabaseInterface::setDeletedMark(MAppBaseObj& item) {
    item.isDeleted_ = true;
}

void DatabaseInterface::removeDeletedMark(MAppBaseObj& item) {
    item.isDeleted_ = false;
}

