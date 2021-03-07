#include "mappBaseObj.h"

MAppBaseObj::MAppBaseObj() {
    code_ = 0;
    isDeleted_ = false;
}

int MAppBaseObj::code() const {
    return code_;
}

bool MAppBaseObj::isDeleted() const {
    return isDeleted_;
}

bool MAppBaseObj::operator ==(const MAppBaseObj& other) const {
    return code_ == other.code();
}

bool MAppBaseObj::operator !=(const MAppBaseObj& other) const {
    return code_ != other.code();
}
