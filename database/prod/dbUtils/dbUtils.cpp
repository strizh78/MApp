#include "dbUtils.h"

template<>
QString QueryFormat::formatValue(const QString& data) {
    QString result;

    for (const auto& ch: data) {
        if (ch == '\'') {
            result.push_back('\\');
        }
        result.push_back(ch);
    }

    return QString("'%1'").arg(result).toUtf8();
};

template<>
QString QueryFormat::formatValue(const QDate& data) {
    return formatValue(data.toString("yyyy-MM-dd"));
}

template<>
QString QueryFormat::formatValue(const QDateTime& data) {
    return formatValue(data.toString("yyyy-MM-dd hh:mm"));
}

template<>
QString QueryFormat::formatValue(const QByteArray& data) {
    return QString(data.toBase64()).toUtf8();
}

QString toString(SQL_OPERATORS value) {
    switch (value) {
    case SQL_OPERATORS::EQ:
        return "=";
    case SQL_OPERATORS::NE:
        return "<>";
    case SQL_OPERATORS::GT:
        return ">";
    case SQL_OPERATORS::LE:
        return "<";
    case SQL_OPERATORS::GTE:
        return ">=";
    case SQL_OPERATORS::LTE:
        return "<=";
    case SQL_OPERATORS::BETWEEN:
        return "BETWEEN";
    case SQL_OPERATORS::LIKE:
        return "LIKE";
    case SQL_OPERATORS::IN:
        return "IN";
    default:
        return "UNDEFINED";
    }
}
