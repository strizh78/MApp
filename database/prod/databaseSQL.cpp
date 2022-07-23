#include "databaseSQL.h"

#include "appointmentDB.h"
#include "eventDB.h"
#include "fileDB.h"
#include "homeopathyDB.h"
#include "medicineDB.h"
#include "patientDB.h"
#include "serviceDB.h"

#include "config.h"

#include <QDebug>
#include <QFile>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>

namespace {
void createTables(QSqlDatabase& db) {
    QFile queries(":/create_tables_queries.txt");

    if (!queries.open(QIODevice::ReadOnly)){
        qCritical() << "Fail to read create_tables_queries";
        return;
    }
    QSqlQuery query(db);

    if (query.exec(QString("USE `%1`").arg(DATABASE_NAME))) {
        qInfo() << "Use " << DATABASE_NAME;
    } else {
        qCritical() << "Fail to use " << DATABASE_NAME;
        qCritical() << db.lastError();
        return;
    }

    while(!queries.atEnd()) {
        QString str = queries.readAll();

        if (query.exec(str)) {
            qInfo() << QString("Tables created successfully");
        } else {
            qCritical() << QString("Fail to create tables");
            qCritical() << query.lastError();
        }
    }
}

void createDatabase(QSqlDatabase& db) {
    QSqlQuery query = db.exec(
        QString(R"(
            CREATE DATABASE IF NOT EXISTS `%1`
            CHARACTER SET utf8
            COLLATE utf8_unicode_ci;
        )").arg(DATABASE_NAME)
    );
    if (query.exec()) {
        qInfo() << QString("Database %1 created").arg(DATABASE_NAME);
    } else {
        qCritical() << QString("Fail to create %1 database").arg(DATABASE_NAME);
        qCritical() << query.lastError();
    }
}

void createDatabaseIfNotExist() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(HOST);
    db.setUserName(ROOT_USER);
    db.setPassword(ROOT_PASSWORD);

    if (!db.isValid()){
        qCritical() << db.lastError();
        return;
    }
    db.open();

    QSqlQuery query = db.exec(QString(R"(
        SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA
        WHERE SCHEMA_NAME = '%1'
    )").arg(DATABASE_NAME));

    switch (query.size()) {
    case -1:
        qCritical() << query.lastError();
    case 0:
        // Database not exists, have to create it and tables.
        createDatabase(db);
        createTables(db);
    case 1:
//        Database exists,
//        but the composition of the tables may have changed
//        TODO: Сhange the processing of updating the composition/structure of tables
        createTables(db);
    default:
        qCritical() << QString("Found multiple databases with name %1").arg(DATABASE_NAME);
    }
    db.close();
}
}

DatabaseSQL::DatabaseSQL() {
    initConnection();

    service = new ServiceDB;
    patient = new PatientDB;
    medicine = new MedicineDB;
    homeopathy = new HomeopathyDB;
    event = new EventDB;

    appointment = new AppointmentDB(
        static_cast<HomeopathyDB*>(homeopathy),
        static_cast<MedicineDB*>(medicine),
        static_cast<ServiceDB*>(service),
        static_cast<PatientDB*>(patient)
    );

    files = new FileDB(static_cast<AppointmentDB*>(appointment));
}

DatabaseSQL::~DatabaseSQL() {
    db_.close();
}

bool DatabaseSQL::initConnection() {
    createDatabaseIfNotExist();

    db_ = QSqlDatabase::addDatabase("QMYSQL", CONNECTION_NAME);
    db_.setHostName(HOST);
    db_.setUserName(ROOT_USER);
    db_.setPassword(ROOT_PASSWORD);
    db_.setDatabaseName(DATABASE_NAME);

    if (db_.open()) {
        qInfo() << "Connection inited";
    } else {
        qCritical() << "Connection failed";
        qCritical() << db_.lastError().text();
        return false;
    }
    QSqlQuery query(db_);

    if (!query.exec(QString("USE `%1`").arg(DATABASE_NAME))) {
        qCritical() << "Fail to use " << DATABASE_NAME;
        qCritical() << db_.lastError().text();
        return false;
    }

    qInfo() << "Use " << DATABASE_NAME;
    return true;
}
