#pragma once

#include <QMetaType>

class MAppBaseObj {
public:
    MAppBaseObj() = default;
    int code() const;
    bool isDeleted() const;

    bool operator ==(const MAppBaseObj& other) const;
    bool operator !=(const MAppBaseObj& other) const;

    friend class DatabaseInterface;

protected:
    int code_ = 0;
    bool isDeleted_ = false;

private:
    void setCode(int code);
    void setDeleted(bool isDelelted);
};

Q_DECLARE_METATYPE(MAppBaseObj);
