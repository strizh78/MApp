#include "timetableUtils.h"

bool isTimeSlotsIntersect(QDateTime b1, QDateTime e1,
                          QDateTime b2, QDateTime e2)
{
    if (b1 > b2) {
        std::swap(b1, b2);
        std::swap(e1, e2);
    }
    return b2 < e1;
}

int toSeconds(const QTime& time) {
    return time.hour() * 60 * 60 + time.minute() * 60 + time.second();
}
