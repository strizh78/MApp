#include "query.h"

#include <QDebug>
#include <QSqlError>

Query::Query(const QSqlDatabase& db, const QString& table)
    : QSqlQuery(db)
    , table_(table)
{}

bool Query::exec() {
    if (QSqlQuery::exec()) {
        return true;
    }
    qCritical() << this->lastError();
    qCritical() << this->lastQuery();
    return false;
}

QString Query::text() const {
    return this->lastQuery();
}

InsertQuery::InsertQuery(const QString& table, const ValueByColumn& valuesByColumn)
    : Query(QSqlDatabase::database(CONNECTION_NAME), table)
{
    this->prepare(INSERT_QUERY_TEMPLATE.arg(
        table_,
        insertColumns(valuesByColumn),
        positionalPlaceholders(valuesByColumn.size())
    ));

    for (const auto& it : valuesByColumn) {
        this->addBindValue(it.second);
    }
}

bool InsertQuery::exec() {
    qInfo() << "Started insert into " << table_;
    bool result = Query::exec();

    if (result) {
        this->prepare(LAST_INSERT_ID_QUERY);
        result = Query::exec();
    }

    QString message = QString("Inserting into %1 %2").arg(
        table_,
        result ? "SUCCESS" : "FAILURE"
    );
    qInfo() << message;
    return result;
}

QString InsertQuery::insertColumns(const ValueByColumn& valuesByColumn) {
    std::vector<QString> columns;

    auto columnFormat = [](QString col) { return QString("`%1`").arg(col); };

    for (const auto& it: valuesByColumn) {
        columns.push_back(columnFormat(it.first));
    }
    return toString(columns, INNER_SEPARATOR);
}

QString InsertQuery::positionalPlaceholders(int n) {
    return toString(std::vector<QString>(n, "?"), ", ");
}

QString WithWhereOption::wherePart() const {
    if (where_.empty()) {
        return "";
    }
    return WHERE_PART_TEMPLATE.arg(toString(where_, " AND "));
}

UpdateQuery::UpdateQuery(const QString& table, const ValueByColumn& valuesByColumn)
    : Query(QSqlDatabase::database(CONNECTION_NAME), table)
{
    update_ = UPDATE_QUERY_TEMPLATE.arg(
        table_,
        updateStatements(valuesByColumn)
    );

    for (const auto& it : valuesByColumn) {
        values_.push_back({PLACEHOLDER_TEMPLATE.arg(it.first), it.second});
    }
}

bool UpdateQuery::exec() {
    qInfo() << QString("Started update item in %1 %2").arg(table_, wherePart());
    this->prepare(text());
    for (const auto& item : values_) {
        this->bindValue(item.first, item.second);
    }
    bool result = Query::exec();
    QString message = QString("Updating item in %1 %2").arg(
        table_,
        result ? "SUCCESS" : "FAILURE"
    );
    qInfo() << message;
    return result;
}

QString UpdateQuery::text() const {
    return update_ + wherePart();
}

QString UpdateQuery::updateStatements(const ValueByColumn& valuesByColumn) {
    std::vector<QString> setStatements;

    for (const auto& value: valuesByColumn) {
        setStatements.push_back(
            SET_STATEMENT_TEMPLATE.arg(
                value.first,
                PLACEHOLDER_TEMPLATE.arg(value.first)
            )
        );
    }
    return toString(setStatements, INNER_SEPARATOR);
}

SelectQuery::SelectQuery(const QString& table, const std::vector<QString>& columns)
    : Query(QSqlDatabase::database(CONNECTION_NAME), table)
    , from_(table)
{
    constructSelectPart(columns);
}

SelectQuery::SelectQuery(const QString& table, const ColumnsWithTable& columnsWithTable)
    : Query(QSqlDatabase::database(CONNECTION_NAME), table)
    , from_(table)
{
    constructSelectPart(columnsWithTable);
}

bool SelectQuery::exec() {
    qInfo() << QString("Start select from %1").arg(table_);
    this->prepare(text());
    bool result = Query::exec();
    QString message = QString("Selecting from %1 %2").arg(
        table_,
        result ? "SUCCESS" : "FAILURE"
    );
    qInfo() << message;
    return result;
}

QString SelectQuery::text() const {
    QString queryText;

    queryText.push_back(SELECT_PART_TEMPLATE.arg(select_));
    queryText.push_back(FROM_PART_TEMPLATE.arg(from_));
    queryText.push_back(wherePart());

    return queryText;
}

void SelectQuery::leftJoin(
    const QString& tableToJoin, const QString& columnToJoin, const QString& mainColumn)
{
    from_.push_back(LEFT_JOIN_TEMPLATE.arg(tableToJoin, columnToJoin, table_, mainColumn));
}

void SelectQuery::leftJoin(
    const QString& tableToJoin, const QString& columnToJoin,
    const QString& mainTable, const QString& mainColumn)
{
    from_.push_back(LEFT_JOIN_TEMPLATE.arg(tableToJoin, columnToJoin, mainTable, mainColumn));
}

void SelectQuery::constructSelectPart(const std::vector<QString>& columns) {
    std::vector<QString> statements;
    auto columnFullName = [&](const QString& column) {
        return SELECT_STATEMENT_TEMPLATE.arg(table_, column);
    };
    for (const QString& column: columns) {
        statements.push_back(columnFullName(column));
    }
    select_ = toString(statements, ",\n");
}

void SelectQuery::constructSelectPart(const ColumnsWithTable& columnsWithTable) {
    std::vector<QString> statements;
    auto columnFullName = [&](const std::pair<QString, QString>& item) {
        return SELECT_STATEMENT_TEMPLATE.arg(item.first, item.second);
    };
    for (const auto& column: columnsWithTable) {
        statements.push_back(columnFullName(column));
    }
    select_ = toString(statements, ",\n");
}

DeleteQuery::DeleteQuery(const QString& table)
: Query(QSqlDatabase::database(CONNECTION_NAME), table)
{}

bool DeleteQuery::exec() {
    qInfo() << QString("Start delete from %1 %2").arg(table_, wherePart());
    this->prepare(text());
    bool result = Query::exec();
    QString message = QString("Deleting from %1 %2").arg(
        table_,
        result ? "SUCCESS" : "FAILURE"
    );
    qInfo() << message;
    return result;
}

QString DeleteQuery::text() const {
    return DELETE_QUERY_TEMPLATE.arg(table_) + wherePart();
}

template<>
QString QueryFormat::formatValue(const SelectQuery& data) {
    return QString("(%1)").arg(data.text());
}
