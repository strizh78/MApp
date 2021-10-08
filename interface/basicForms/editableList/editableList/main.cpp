#include "editableWidget.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    EditableWidget w;
    w.show();
    return a.exec();
}
