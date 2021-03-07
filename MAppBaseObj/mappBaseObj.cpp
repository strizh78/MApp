#include "mappBaseObj.h"

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

void MAppBaseObj::setCode(int code) {
    code_ = code;
}

void MAppBaseObj::setDeleted(bool isDelelted) {
    isDeleted_ = isDelelted;
}
