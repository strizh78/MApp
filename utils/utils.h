#pragma once

#include <QString>
#include <QVariant>

#include <vector>
#include <sstream>

QString toString(const std::vector<QString>& src, std::string sep = " ");
QString toString(QStringList::iterator begin, QStringList::iterator end, const std::string& sep = " ");

template <class T>
QString toString(const std::vector<T>& src, std::string sep = " ") {
    std::ostringstream oss;

    if (!src.empty()) {
        std::copy(src.begin(), src.end() - 1, std::ostream_iterator<T>(oss, sep));
        oss << src.back();
    }
    return QString::fromStdString(oss.str());
}
