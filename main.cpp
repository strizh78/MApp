#include "interface/mainwindow.h"

#include "database/test/databaseTest.h"

#include <QApplication>
#include <QTranslator>
#include <QGuiApplication>
#include <QCoreApplication>

#include <memory>

void setupScaleDpiUiFlags() {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication::setAttribute(Qt::AA_Use96Dpi);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);

    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1.5");
    qputenv("QT_ENABLE_HIGHDPI_SCALING", "1");
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
}

int main(int argc, char *argv[]) {
    setupScaleDpiUiFlags();

    DatabasePtr database = std::make_shared<DatabaseTest>();

    QApplication a(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load(":/qtbase_ru.qm");
    a.installTranslator(&qtTranslator);

    MainWindow w(database);
    w.show();
    return a.exec();
}
