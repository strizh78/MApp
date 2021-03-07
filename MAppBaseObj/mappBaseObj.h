#pragma once

#include <QMetaType>

class MAppBaseObj {
public:
    MAppBaseObj();
    int code() const;
    bool isDeleted() const;

    bool operator ==(const MAppBaseObj& other) const;
    bool operator !=(const MAppBaseObj& other) const;

    friend class DatabaseInterface;

protected:
    int code_;
    bool isDeleted_;
};

Q_DECLARE_METATYPE(MAppBaseObj);
