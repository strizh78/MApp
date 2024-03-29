#pragma once

#include <QMetaType>

class MAppBaseObj {
public:
    MAppBaseObj() = default;
    int code() const;
    bool isDeleted() const;

    bool isExists() const;

    bool operator ==(const MAppBaseObj& other) const;
    bool operator !=(const MAppBaseObj& other) const;

    template <class BaseItem>
    friend class ItemDBInterface;

protected:
    int code_ = 0;
    bool isDeleted_ = false;

private:
    void setCode(int code);
    void setDeleted(bool isDelelted);
};

Q_DECLARE_METATYPE(MAppBaseObj);
Q_DECLARE_METATYPE(const MAppBaseObj*);
