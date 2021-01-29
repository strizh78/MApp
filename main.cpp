#include "interface/mainwindow.h"

#include "database/databasetest.h"

#include "tests/servicetests.h"
#include "tests/patientTests.h"

#include <QApplication>
#include <QTranslator>

#include <memory>

void runTests(std::shared_ptr<DatabaseInterface> database, int argc, char *argv[]) {
//    QTest::qExec(new ServiceTests, argc, argv); [need fix]
    QTest::qExec(new PatientTests(database), argc, argv);
}

int main(int argc, char *argv[])
{
    std::shared_ptr<DatabaseInterface> database = std::make_shared<DatabaseTest>();

    QApplication a(argc, argv);
    runTests(database, argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load(":/qtbase_ru.qm");
    a.installTranslator(&qtTranslator);

    MainWindow w(database);
    w.show();
    return a.exec();
}
