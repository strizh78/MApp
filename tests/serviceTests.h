#pragma once

#include "database/databaseinterface.h"

#include <QObject>
#include <QTest>
#include <QtTest/QtTest>

class ServiceTests : public QObject
{
    Q_OBJECT
public:
    explicit ServiceTests(std::shared_ptr<DatabaseInterface> database,
                          QObject *parent = nullptr);
private slots:
    void createService();
    void editService();

private:
    std::shared_ptr<DatabaseInterface> database_;
};
