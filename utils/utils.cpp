#include "utils.h"

#include "patient/patient.h"
#include "service/service.h"
#include "drugs/homeopathy.h"
#include "drugs/medicines.h"
#include "appointment/appointment.h"
#include "file/file.h"
#include "interface/basicForms/mappTable.h"

#include <QPainter>

QString toString(QStringList::iterator begin, QStringList::iterator end, const std::string& sep) {
    QString result;

    for (auto it = begin; it != end; ++it) {
        result.push_back(QString(*it) + QString::fromStdString(sep));
    }
    result.chop(sep.size());

    return result;
}

QString toString(const std::vector<QString>& src, std::string sep) {
    QString result;

    for (const auto& x : src) {
        result += x + QString::fromStdString(sep);
    }
    result.resize(result.size() - sep.size());

    return result;
}
