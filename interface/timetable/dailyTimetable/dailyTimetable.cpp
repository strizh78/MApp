#include "dailyTimetable.h"

#include "interface/timetable/timetableEvent.h"

#include "events/dailyTimetableArchive.h"
#include "events/dailyTimetableEvent.h"

#include "interface/interfaceUtils.h"

#include <QVBoxLayout>

DailyTimetable::DailyTimetable(QWidget *parent)
    : QWidget(parent)
    , date_(QDate::currentDate())
{
    setAttribute(Qt::WA_LayoutUsesWidgetRect);
    setBackgroundRole(QPalette::Base);

    auto lay = new QVBoxLayout();
    lay->setSpacing(25 - 9);
    lay->addStretch();

    setLayout(lay);
}

void DailyTimetable::setDate(QDate date) {
    date_ = date;
}

void DailyTimetable::setDatabase(DatabasePtr database) {
    database_ = database;
}

void DailyTimetable::updateData(const std::vector<TimetableEvent>& tevents) {
    auto previousArchive = this->findChild<DailyTimetableArchive*>("archiveWidget" + date_.toString("dd.mm"));
    bool archiveVisible = (previousArchive) ? previousArchive->isVisible() : false;
    bool archiveChecked = (previousArchive) ? previousArchive->isChecked() : false;
    archiveChecked |= (date_ < QDate::currentDate());

    auto lay = static_cast<QVBoxLayout*>(layout());
    clearLayout(lay);


    auto* archiveWidget = new DailyTimetableArchive(database_, this);
    archiveWidget->setObjectName("archiveWidget" + date_.toString("dd.mm"));
    lay->insertWidget(lay->count(), archiveWidget);

    for (size_t i = 0; i < tevents.size(); ++i) {
        if (date_ > QDate::currentDate() ||
            (QDate::currentDate() == date_ && tevents[i].end >= QTime::currentTime()))
        {
            auto* eventWidget = new DailyTimetableEvent(tevents[i], database_, this);
            lay->insertWidget(lay->count(), eventWidget);
        } else {  
            archiveVisible = true;
            archiveWidget->addEvent(tevents[i]);
        }
    }

    archiveWidget->setVisible(archiveVisible);
    archiveWidget->setChecked(archiveChecked);
    lay->setContentsMargins(25, 25 - 9 * (!archiveVisible), 50, /*не согласовано*/20);

    if (tevents.size() > 0) {
        lay->addStretch();
    } else {
        QLabel* label = new QLabel("На этот день нет запланированных приемов", this);
        label->setStyleSheet("color:rgb(180, 180, 180);");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        changeFont(label, 18, QFont::Medium);
        lay->insertWidget(lay->count(), label);
    }
}
