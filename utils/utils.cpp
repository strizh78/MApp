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


std::vector<QString> qStringListToVector(const QStringList list) {
    std::vector<QString> result;

    for (const auto& str : list) {
        result.push_back(str);
    }
    return result;
}

std::vector<QString> split(const QString& str, const std::string& sep) {
    return qStringListToVector(str.split(QString::fromStdString(sep)));
}

QString getApplicatonDirectory() {
    QDir dir;

#ifdef Q_OS_MACOS
    dir.cd("../../..");
#endif

    return dir.absolutePath();
}
