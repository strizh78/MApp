#pragma once

#include "config.h"
#include "query.h"

#include "database/itemDatabaseInterface.h"
#include "MAppBaseObj/mappBaseObj.h"

#include "utils/utils.h"

#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <vector>

const std::string MULTIPLE_VALUE_SEPARATOR = ";;";

template <class BaseItem>
class ItemDBProdInterface : public ItemDBInterface<BaseItem> {
public:
    ItemDBProdInterface() = default;
    virtual ~ItemDBProdInterface() = default;
//    TODO: Add filters
    void list(std::vector<BaseItem>& receiver) override {
        SelectQuery query(tableName_, columns_);

        if (query.exec()) {
            handleListResult(query, receiver);
        }
    }

    void add(BaseItem& item) override {
        InsertQuery query(tableName_, valuesToUpsert(item));

        if (!query.exec() || !query.first()) {
            return;
        }

        int code = query.value(0).toInt();

        if (code == 0) {
            qCritical() << "Failed to read inserted ID";
            return;
        }

        this->setCode(item, code);
    }

    void update(const BaseItem& editedItem) override {
        UpdateQuery query(tableName_, valuesToUpsert(editedItem));

        query.addWhereStatement("id", SQL_OPERATORS::EQ, editedItem.code());
        query.exec();
    }

    QString getTableName() const {
        return tableName_;
    }

    std::vector<QString> getColumns() const {
        return columns_;
    }

    virtual BaseItem rowToItem(const QSqlQuery& row, int startPos = 0) = 0;

protected:
    virtual void handleListResult(QSqlQuery& query, std::vector<BaseItem>& receiver) {
        while (query.next()) {
            receiver.push_back(rowToItem(query));
        }
    }
    virtual ValueByColumn valuesToUpsert(const BaseItem& item) = 0;

protected:
    QString tableName_;
    std::vector <QString> columns_;
};
