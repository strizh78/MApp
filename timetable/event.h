#pragma once

#include "MAppBaseObj/mappBaseObj.h"

#include <QString>
#include <QDateTime>
#include <QTime>

class Event : public MAppBaseObj {
public:
    Event(QString title, QDateTime dateTime, QTime duration);

    bool operator < (const Event& other) const;

    QString title;
    QDateTime dateTime;
    QTime duration;
    QString comment;
};
