#pragma once

#include <QString>
#include <QLabel>

#include <vector>
#include <sstream>

namespace ErrorLog {
void showItemFormWarning(QLabel* errorText, const std::vector<QString>& wrongFields);
}

QString toString(const std::vector<QString>& src, std::string sep = " ");

template <class T>
QString toString(const std::vector<T>& src, std::string sep = " ") {
    std::ostringstream oss;

    if (!src.empty()) {
        std::copy(src.begin(), src.end() - 1, std::ostream_iterator<T>(oss, sep));
        oss << src.back();
    }
    return QString::fromStdString(oss.str());
}
