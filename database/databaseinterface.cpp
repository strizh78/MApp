#include "databaseinterface.h"

void DatabaseInterface::setCode(MAppBaseObj& item) {
    item.setCode(getNextCode());
}

void DatabaseInterface::setCodeToEdit(MAppBaseObj& item, int code) {
    item.setCode(code);
}

void DatabaseInterface::setDeletedMark(MAppBaseObj& item) {
    item.setDeleted(true);
}

void DatabaseInterface::removeDeletedMark(MAppBaseObj& item) {
    item.setDeleted(false);
}

