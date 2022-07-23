#pragma once

#include "database/databaseInterface.h"

#include <QSqlDatabase>


class DatabaseSQL : public DatabaseInterface {
public:
    DatabaseSQL();
    ~DatabaseSQL();

protected:
    QSqlDatabase db_;

private:
    bool initConnection();
};
