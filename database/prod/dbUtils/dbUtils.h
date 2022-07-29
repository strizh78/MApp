#pragma once

#include "database/prod/config.h"
#include "utils/utils.h"

#include <QString>
#include <QDate>
#include <QDateTime>

enum class SQL_OPERATORS {
    EQ,
    NE,
    GT,
    LE,
    GTE,
    LTE,
    BETWEEN,
    LIKE,
    IN,
};

QString toString(SQL_OPERATORS value);

namespace QueryFormat {
template <class T>
QString formatValue(const T& data) {
    return QString("%1").arg(data);
};

template <class T>
QString formatValue(const std::vector<T>& data) {
    std::vector<QString> result;

    for (const auto& item : data) {
        result.push_back(formatValue(item));
    }
    return QString("[%1]").arg(toString(result, ","));
}

template <>
QString formatValue(const QString& data);

template <>
QString formatValue(const QDate& data);

template <>
QString formatValue(const QDateTime& data);

template <>
QString formatValue(const QByteArray& data);
}
