#pragma once

#include "dbUtils/dbUtils.h"

#include <QString>
#include <QSqlQuery>

#include <vector>

using ValueByColumn = std::vector<std::pair<QString, QVariant>>;
using ColumnsWithTable = std::vector<std::pair<QString, QString>>;

class Query : public QSqlQuery {
public:
    Query(const QSqlDatabase& db, const QString& table);
    virtual ~Query() = default;
    virtual bool exec();
    virtual QString text() const;

protected:
    const std::string INNER_SEPARATOR = ",\n\t";

protected:
    QString table_;
};


class InsertQuery : public Query {
public:
    InsertQuery(const QString& table, const ValueByColumn& valuesByColumn);
    bool exec() override;

private:
    QString insertColumns(const ValueByColumn& valuesByColumn);
    QString positionalPlaceholders(int n);

private:
    const QString INSERT_QUERY_TEMPLATE = "INSERT INTO %1 (%2) VALUES (%3);";
    const QString LAST_INSERT_ID_QUERY = "SELECT LAST_INSERT_ID();";
};


class WithWhereOption {
public:
    template<class T>
    void addWhereStatement(const QString& column, SQL_OPERATORS oper, const T& statement) {
        where_.push_back(QString("`%1` %2 %3").arg(
            column,
            toString(oper),
            QueryFormat::formatValue(statement)
        ));
    }

protected:
    QString wherePart() const;

private:
    const QString WHERE_PART_TEMPLATE = "\nWHERE\n %1";

private:
    std::vector<QString> where_;
};


class UpdateQuery : public Query, public WithWhereOption {
public:
    UpdateQuery(const QString& table, const ValueByColumn& valuesByColumn);
    bool exec() override;
    QString text() const override;

private:
     QString updateStatements(const ValueByColumn& valuesByColumn);

private:
    const QString UPDATE_QUERY_TEMPLATE = "UPDATE %1 SET %2";
    const QString SET_STATEMENT_TEMPLATE = "`%1` = %2";
    const QString PLACEHOLDER_TEMPLATE = ":%1";

private:
    ValueByColumn values_;
    QString update_;
};

class SelectQuery : public Query, public WithWhereOption {
public:
    SelectQuery(const QString& table, const std::vector<QString>& columns);
    SelectQuery(const QString& table, const ColumnsWithTable& columnsWithTable);
    bool exec() override;
    QString text() const override;
    void leftJoin(const QString& tableToJoin, const QString& columnToJoin, const QString& mainColumn);
    void leftJoin(
        const QString& tableToJoin, const QString& columnToJoin,
        const QString& mainTable, const QString& mainColumn
    );

private:
    void constructSelectPart(const std::vector<QString>& columns);
    void constructSelectPart(const ColumnsWithTable& columnsWithTable);

private:
    const QString SELECT_PART_TEMPLATE = "SELECT\n%1";
    const QString SELECT_STATEMENT_TEMPLATE = "`%1`.`%2`";
    const QString FROM_PART_TEMPLATE = "\nFROM\n %1";
    const QString LEFT_JOIN_TEMPLATE = "\nLEFT JOIN `%1` ON `%1`.`%2` = `%3`.`%4`";

private:
    QString select_;
    QString from_;
};


class DeleteQuery : public Query, public WithWhereOption {
public:
    DeleteQuery(const QString& table);
    bool exec() override;
    QString text() const override;

private:
    const QString DELETE_QUERY_TEMPLATE = "DELETE FROM %1";
};

namespace QueryFormat {
template <>
QString formatValue(const SelectQuery& data);
}
