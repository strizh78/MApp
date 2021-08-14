#include "interface/mainwindow.h"

#include "database/databasetest.h"

#include <QApplication>
#include <QTranslator>

#include <memory>

int main(int argc, char *argv[])
{
    std::shared_ptr<DatabaseInterface> database = std::make_shared<DatabaseTest>();

    QApplication a(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load(":/qtbase_ru.qm");
    a.installTranslator(&qtTranslator);

    MainWindow w(database);
    w.show();
    return a.exec();
}
