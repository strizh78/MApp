#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "interface/medicine/medicineDrugListForm.h"
#include "interface/homeopathy/homeopathyDrugListForm.h"
#include "interface/service/servicesListForm.h"
#include "interface/patient/patientsListForm.h"
#include "interface/appointment/appointmentsListForm.h"
#include "interface/timetable/timetableForm.h"

MainWindow::MainWindow(DatabasePtr database,
                       QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , database_(database)
{
    ui->setupUi(this);

    ui->widget->setBurgerIcons(QIcon(":/icons/burgerMenu/hamburger.png"),
                              QIcon(":/icons/burgerMenu/close.png"));

    QAction *mainAction = addActionToMenu(QIcon(":/icons/burgerMenu/home.png"), "Главная страница",
                                          &MainWindow::on_timetable_clicked);
    mainAction->trigger();

    addActionToMenu(QIcon(":/icons/burgerMenu/health-and-care.png"), "Услуги",
                    &MainWindow::on_servicesList_clicked);
    addActionToMenu(QIcon(":/icons/burgerMenu/patient.png"), "Пациенты",
                    &MainWindow::on_patientsList_clicked);
    addActionToMenu(QIcon(":/icons/burgerMenu/pills.png"), "Лекарства",
                    &MainWindow::on_medicineList_clicked);
    addActionToMenu(QIcon(":/icons/burgerMenu/drugs.png"), "Гомеопатические препараты",
                    &MainWindow::on_homeopathyList_clicked);
    addActionToMenu(QIcon(":/icons/burgerMenu/medical-history.png"), "Приёмы",
                    &MainWindow::on_appointmentsList_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

template <class T>
void MainWindow::openWidget() {
    if (!ui->formLayout->isEmpty()) {
        auto* currentWidget = ui->formLayout->itemAt(0)->widget();
        if (currentWidget) {
            currentWidget->close();
            ui->formLayout->removeWidget(currentWidget);
            delete currentWidget;
        }
    }

    QWidget* newWidget = new T(database_);
    ui->formLayout->addWidget(newWidget);
}

void MainWindow::on_servicesList_clicked() {
    openWidget<ServicesListForm>();
}

void MainWindow::on_medicineList_clicked() {
    openWidget<MedicineDrugListForm>();
}

void MainWindow::on_patientsList_clicked() {
    openWidget<PatientsListForm>();
}

void MainWindow::on_homeopathyList_clicked() {
    openWidget<HomeopathyDrugListForm>();
}

void MainWindow::on_appointmentsList_clicked() {
    openWidget<AppointmentsListForm>();
}

void MainWindow::on_timetable_clicked() {
    openWidget<TimetableForm>();
}

template <class F>
QAction* MainWindow::addActionToMenu(const QIcon& icon, const QString& text, F slotName) {
    QAction *action = new QAction(icon, text);
    connect(action, &QAction::triggered, this, slotName);

    ui->widget->addMenuAction(action);
    return action;
}
