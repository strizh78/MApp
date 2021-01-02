#include "interface/mainwindow.h"

#include "database/databasetest.h"

#include "tests/servicetests.h"

#include <QApplication>
#include <QTranslator>

#include <memory>

void runTests(int argc, char *argv[]) {
    QTest::qExec(new ServiceTests, argc, argv);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    runTests(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load(":/qtbase_ru.qm");
    a.installTranslator(&qtTranslator);

    std::shared_ptr<DatabaseInterface> database = std::make_shared<DatabaseTest>();

    MainWindow w(database);
    w.show();
    return a.exec();
}
