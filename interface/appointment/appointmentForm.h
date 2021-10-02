#pragma once

#include "appointment/appointment.h"
#include "database/databaseInterface.h"

#include <QWidget>

namespace Ui {
class AppointmentForm;
}

class AppointmentForm : public QWidget {
    Q_OBJECT

public:
    AppointmentForm(DatabasePtr database,
                    std::optional<Appointment> appointment = std::nullopt,
                    QWidget *parent = nullptr);
    ~AppointmentForm();
signals:
    void appointmentCreateSignal(const Appointment& created);
    void appointmentEditSignal(const Appointment& editedPatient);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_solutionBox_accepted();
    void on_solutionBox_rejected();

    void on_patientChooseBtn_clicked();
    void on_serviceChooseBtn_clicked();
    void on_homeopathyChooseBtn_clicked();
    void on_addMedicinesBtn_clicked();

    void on_dateEdit_dateChanged(const QDate &date);
    void on_timeEdit_timeChanged(const QTime &time);

    void on_patientViewBtn_clicked();
    void on_serviceViewBtn_clicked();

    void on_openRecordBtn_clicked(bool checked);
    void on_copyAppointmentBtn_clicked();

private slots:
    void patientChoosed(QVariant data);
    void serviceChoosed(QVariant data);
    void homeopathyChoosed(QVariant data);
    void medicineChoosed(std::vector<QVariant> data);

    void on_homeopathyViewBtn_clicked();

    void on_conductAppointmentBtn_clicked();

private:
    void setupCreateUi();
    void setupAppointmentTimeType();
    void setupEditUi();
    void setupStatus();

    void setEditFieldsEnabled(bool enabled);
    void hideDrugs();
    void setRecordVisible(bool visible);

    void fillAppointmentInfo();

    template <class T, class CreateRowFunc, class RowChooseSlot>
    void showSingleSelectionForm(ItemDBInterface<T>* databaseItem, CreateRowFunc createRowFunc,
                                 RowChooseSlot chooseSlot, const T& itemSelected);

private:
    Ui::AppointmentForm *ui;
    DatabasePtr database_;

    Appointment currentAppointment_;

    bool isHeldNow = false;
};
