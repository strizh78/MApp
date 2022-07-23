#include "interface/mainwindow.h"

#include "database/test/databaseTest.h"
#include "database/prod/databaseSQL.h"
#include "utils/utils.h"

#include <memory>

#include <QApplication>
#include <QDirIterator>
#include <QFontDatabase>
#include <QTranslator>
#include <QGuiApplication>
#include <QCoreApplication>

void setupScaleDpiUiFlags() {
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication::setAttribute(Qt::AA_Use96Dpi);
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);

    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1.5");
    qputenv("QT_ENABLE_HIGHDPI_SCALING", "1");
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
}

void setApplicationFontFamily() {
    QDirIterator it(getApplicatonDirectory() + "/fonts", QStringList() << "*.ttf", QDir::Files);
    int id;
    while (it.hasNext()) {
        auto filename = it.next();
        id = QFontDatabase::addApplicationFont(filename);
    }
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont montserrat(family);

    qApp->setFont(montserrat);
}

int main(int argc, char *argv[]) {
    setupScaleDpiUiFlags();

    DatabasePtr database = std::make_shared<DatabaseSQL>();

    QApplication a(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load(":/qtbase_ru.qm");
    a.installTranslator(&qtTranslator);

    setApplicationFontFamily();

    MainWindow w(database);

    QPalette p = a.palette();
    if (a.palette().base().color() == QColor(255, 255, 255)) {
        p.setColor(QPalette::Active, QPalette::Base, QColor(237, 238, 240));
        p.setBrush(QPalette::Active, QPalette::Window, QColor(255, 255, 255));
        p.setColor(QPalette::Inactive, QPalette::Window, QColor(248, 248, 248));
    } else {
        p.setBrush(QPalette::Base, QColor(35, 35, 35));
        p.setBrush(QPalette::Window, QColor(52, 52, 52));
    }
    qApp->setPalette(p);

    w.show();

    return a.exec();
}
