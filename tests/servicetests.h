#pragma once

#include "database/databaseinterface.h"

#include <QObject>
#include <QTest>
#include <QtTest/QtTest>

class ServiceTests : public QObject
{
    Q_OBJECT
public:
    explicit ServiceTests(QObject *parent = nullptr);
private slots:
    void CreateService();

private:
    std::shared_ptr<DatabaseInterface> database_;
};
